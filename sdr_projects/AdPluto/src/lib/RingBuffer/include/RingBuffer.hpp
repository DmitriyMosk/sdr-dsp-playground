#ifndef _LIB_CONTAINER_RINGBUFFER
#define _LIB_CONTAINER_RINGBUFFER

#include <cstdint>
#include <atomic> 
#include <cassert>
#include <thread>
#include <memory>

constexpr size_t CacheLineSize = 64; //bytes

template <typename T> 
class RingBuffer { 
public: 
    explicit RingBuffer(size_t capacity) 
        : capacity_(capacity), mask_(capacity - 1), 
        is_active_(true), buffer_(new T[capacity])
    {
        assert((capacity & mask_) == 0 && "Capacity must be power of two");
    }
    
    ~RingBuffer();
    
    bool Pull(T &val); 
    bool Push(const T &val);
    
    size_t UsedSize(); 
    size_t GetMaxSize();

    bool Reset(); 
private:
    void Shutdown();

    std::unique_ptr<T[]> buffer_;

    const size_t capacity_; 
    const size_t mask_;

    /**
     * Выравнивание нужно для того, чтобы разместить счётчики в разных кеш-линиях
     */
    alignas(CacheLineSize) std::atomic<size_t> read_idx_{0}; 
    alignas(CacheLineSize) std::atomic<size_t> write_idx_{0}; 
    alignas(CacheLineSize) std::atomic<bool>   is_active_;
};

template class RingBuffer<double>; 
template class RingBuffer<float>; 
template class RingBuffer<short>;
template class RingBuffer<bool>;
template class RingBuffer<int>; 
template class RingBuffer<unsigned int>;

template class RingBuffer<int8_t>; 
template class RingBuffer<int64_t>;

template class RingBuffer<uint8_t>;
template class RingBuffer<uint16_t>; 
template class RingBuffer<uint64_t>;  
#endif 