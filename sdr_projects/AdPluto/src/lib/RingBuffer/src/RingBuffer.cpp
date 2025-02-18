#include "RingBuffer.hpp" 

template<typename T>
RingBuffer<T>::~RingBuffer() {
    Shutdown(); 
}

template<typename T> 
bool RingBuffer<T>::Push(const T &val) { 
    if (!is_active_.load(std::memory_order_acquire)) // Проверка активности
        return false;

    const size_t write_idx = write_idx_.load(std::memory_order_relaxed);
    const size_t next_idx = write_idx + 1;
        
    if (next_idx - read_idx_.load(std::memory_order_acquire) > capacity_) {
        return false; // Буфер полон
    }
        
    buffer_[write_idx & mask_] = val;
    write_idx_.store(next_idx, std::memory_order_release);
    return true; 
}

template<typename T> 
bool RingBuffer<T>::Pull(T &val) {
    if (!is_active_.load(std::memory_order_acquire))
        return false;

    const size_t read_idx = read_idx_.load(std::memory_order_relaxed);
        
    if (read_idx == write_idx_.load(std::memory_order_acquire)) {
        return false;
    }
        
    val = buffer_[read_idx & mask_];
    read_idx_.store(read_idx + 1, std::memory_order_release);
    return true;
}

template<typename T>
size_t RingBuffer<T>::UsedSize() {
    const size_t write_idx = write_idx_.load(std::memory_order_acquire);
    const size_t read_idx = read_idx_.load(std::memory_order_acquire);

    return write_idx - read_idx;
}

template<typename T>
size_t RingBuffer<T>::GetMaxSize() { 
    return capacity_; 
}

template<typename T> 
bool RingBuffer<T>::Reset() {
    Shutdown();
    buffer_.reset(new T[capacity_]); // Пересоздаем буфер
    write_idx_.store(0, std::memory_order_relaxed);
    read_idx_.store(0, std::memory_order_relaxed);
    is_active_.store(true, std::memory_order_release);

    return true;
}

template<typename T> 
void RingBuffer<T>::Shutdown() {
    is_active_.store(false, std::memory_order_release);

    while (write_idx_.load(std::memory_order_acquire) != 
           read_idx_.load(std::memory_order_acquire)) {
        std::this_thread::yield();
    }
}
