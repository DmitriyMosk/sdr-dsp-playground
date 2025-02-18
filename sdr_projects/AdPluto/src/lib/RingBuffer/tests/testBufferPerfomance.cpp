#include "benchmark/benchmark.h"
#include "RingBuffer.hpp"
#include <thread>
#include <xmmintrin.h>


constexpr size_t BUFFER_SIZE     = 1024;    // Должно быть степенью двойки
constexpr size_t TEST_ITERATIONS = 1;       // Увеличим для точности измерений

// Тест записи в одном потоке
static void BM_RingBuffer_Push_1T(benchmark::State& state) {
    RingBuffer<int> rb(BUFFER_SIZE);
    for (auto _ : state) {
        for (size_t i = 0; i < state.range(0); ++i) {
            if (!rb.Push(i)) {
                state.SkipWithError("Buffer overflow");
                return;
            }
        }
        state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
    }
}
BENCHMARK(BM_RingBuffer_Push_1T)->Arg(TEST_ITERATIONS);

// // Тест чтения в одном потоке
// static void BM_RingBuffer_Pull_1T(benchmark::State& state) {
//     RingBuffer<int> rb(BUFFER_SIZE);
//     // Предварительное заполнение буфера
//     for (size_t i = 0; i < state.range(0); ++i) {
//         rb.Push(i);
//     }
    
//     int val;
//     for (auto _ : state) {
//         for (size_t i = 0; i < state.range(0); ++i) {
//             if (!rb.Pull(val)) {
//                 state.SkipWithError("Buffer underflow");
//                 return;
//             }
//             benchmark::DoNotOptimize(val);
//         }
//         state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
//     }
// }
// BENCHMARK(BM_RingBuffer_Pull_1T)->Arg(TEST_ITERATIONS);

// // Тест на переполнение
// static void BM_RingBuffer_Overflow(benchmark::State& state) { 
//     RingBuffer<int> rb(BUFFER_SIZE);
//     // Заполняем буфер полностью
//     for (size_t i = 0; i < BUFFER_SIZE; ++i) {
//         rb.Push(i);
//     }
    
//     for (auto _ : state) {
//         bool result = rb.Push(0); // Попытка записи в заполненный буфер
//         if (result) {
//             state.SkipWithError("Overflow not detected");
//             return;
//         }
//     }
// }
// BENCHMARK(BM_RingBuffer_Overflow);

// // Тест SPSC (один продюсер, один консьюмер)
// static void BM_RingBuffer_SPSC(benchmark::State& state) {
//     RingBuffer<int> rb(BUFFER_SIZE);
//     std::atomic<bool> running{true};
//     int checksum = 0;

//     // Поток-продюсер
//     std::thread producer([&]() {
//         for (size_t i = 0; i < state.range(0); ++i) {
//             while (!rb.Push(i)) {
//                 // Буфер полон - стратегия ожидания
//                 _mm_pause();
//             }
//         }
//         running.store(false, std::memory_order_release);
//     });

//     // Поток-консьюмер
//     std::thread consumer([&]() {
//         int val;
//         while (running.load(std::memory_order_acquire)) {
//             if (rb.Pull(val)) {
//                 checksum += val;
//             } else {
//                 _mm_pause();
//             }
//         }
//     });

//     producer.join();
//     consumer.join();
    
//     // Проверка контрольной суммы
//     const int expected = (state.range(0)-1)*state.range(0)/2;
//     if (checksum != expected) {
//         state.SkipWithError("Data corruption detected");
//     }
    
//     state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
// }
// BENCHMARK(BM_RingBuffer_SPSC)->Arg(TEST_ITERATIONS);

// // Сравнение с std::vector
// static void BM_Vector_SPSC(benchmark::State& state) {
//     std::vector<int> vec;
//     std::mutex mtx;
//     std::atomic<bool> running{true};
//     int checksum = 0;

//     std::thread producer([&]() {
//         for (size_t i = 0; i < state.range(0); ++i) {
//             std::lock_guard<std::mutex> lock(mtx);
//             vec.push_back(i);
//         }
//         running.store(false, std::memory_order_release);
//     });

//     std::thread consumer([&]() {
//         while (running.load(std::memory_order_acquire)) {
//             std::lock_guard<std::mutex> lock(mtx);
//             if (!vec.empty()) {
//                 checksum += vec.back();
//                 vec.pop_back();
//             }
//         }
//     });

//     producer.join();
//     consumer.join();
    
//     state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(int));
// }
// BENCHMARK(BM_Vector_SPSC)->Arg(TEST_ITERATIONS);

BENCHMARK_MAIN();