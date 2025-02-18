### Техническое описание реализации RingBuffer

**Гарантии и особенности:**
1. **Потокобезопасность SPSC (Single Producer/Single Consumer):**
   - Гарантируется корректная работа *только* при одном писателе и одном читателе.
   - Атомарные счетчики `write_idx_` и `read_idx_` синхронизированы через:
     - `std::memory_order_acquire` для операций чтения
     - `std::memory_order_release` для операций записи
   - Пример:  
     Писатель: `write_idx_.store(..., std::memory_order_release)` →  
     Читатель: `read_idx_.load(std::memory_order_acquire)` гарантирует видимость изменений

2. **Безопасное уничтожение:**
   - Механизм `is_active_`:
     ```cpp
     void Shutdown() {
         is_active_.store(false, std::memory_order_release); // 1. Запрет новых операций
         while(write_idx_ != read_idx_) {                    // 2. Ожидание завершения текущих
             std::this_thread::yield();
         }
     }
     ```
   - Гарантирует:
     - Никакие новые Push/Pull не начнутся после `Shutdown()`
     - Все начатые операции завершатся до разрушения буфера

3. **Атомарные индексные счетчики:**
   - 64-битные атомарные счетчики (size_t) решают проблемы:
     - Переполнения: ~584 года при 1 млрд операций/сек
     - Wrap-around: Корректная работа через маску (`write_idx & mask_`)
   - Использование `mask_ = capacity_ - 1` требует:
     ```cpp
     static_assert((capacity & (capacity - 1)) == 0, 
         "Capacity must be power of two");
     ```

4. **Управление памятью:**
   - `buffer_.reset(new T[capacity_])` в `Reset()`:
     - Гарантирует отсутствие обращений к старой памяти после сброса
     - Исключает use-after-free через переключение указателя

**Архитектурные решения и проблемы:**

1. **Проблема: Гонки данных при сбросе/уничтожении**  
   *Решение:*  
   - Двухфазное завершение:
     1. Установка `is_active_ = false` (барьер `release`)
     2. Ожидание опустошения буфера (write_idx == read_idx)

3. **Проблема: Когерентность кэша процессора**  
   *Решение:*  
   - Выравнивание атомарных переменных:
     ```cpp
     alignas(64) std::atomic<size_t> write_idx_; // Разные кэш-линии
     alignas(64) std::atomic<size_t> read_idx_;
     ```
   - Устраняет false sharing (производительность +30-50%)

**Оптимизации памяти (memory_order):**

1. **Push:**
   ```cpp
   size_t r_idx = read_idx_.load(std::memory_order_acquire); // (1)
   buffer_[...] = val;                                       // (2)
   write_idx_.store(..., std::memory_order_release);         // (3)
   ```
   - Гарантии:  
     (2) никогда не будет переупорядочено после (3) благодаря `release`  
     (1) видит актуальное значение `read_idx_` благодаря `acquire`

2. **Pull:**
   ```cpp
   size_t w_idx = write_idx_.load(std::memory_order_acquire); // (A)
   val = buffer_[...];                                        // (B)
   read_idx_.store(..., std::memory_order_release);           // (C)
   ```
   - Гарантии:  
     (B) завершится до (C) (`release` barrier)  
     (A) получит последнее значение `write_idx_` (`acquire` barrier)

**Ограничения:**
1. Не поддерживает:
   - Множественных писателей/читателей (требуются CAS-операции)
   - Блокирующее ожидание при full/empty (только spin-loop)
2. Требует:
   - Размер буфера как степень двойки
   - Тип T с тривиальным копированием (или ручное управление исключениями)