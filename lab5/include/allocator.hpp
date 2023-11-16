#ifndef ALLOCATOR
#define ALLOCATOR

#define NOT_DEBUG

#include<vector>
#include<iostream>

namespace lab {

template<class T, size_t N>
class Allocator {

  private:
    std::vector<T> used_blocks;
    std::vector<void*> free_blocks;
    size_t free_count;

  public:
    static constexpr size_t max_count = N;
    using value_type                  = T;
    using pointer                     = T*;
    using const_pointer               = const T*;
    using size_type                   = size_t;

    Allocator() {
        used_blocks.resize(max_count);
        free_blocks.resize(max_count);

        for(size_t i = 0; i < max_count; ++i) {
            free_blocks[i] = &(used_blocks[i]);
        }

        free_count = max_count;
        #ifdef DEBUG
        std::cout << "I constructed\n";
        #endif
    }

    ~Allocator() {
        used_blocks.clear();
        free_blocks.clear();
        #ifdef DEBUG
        std::cout << "I destructed\n";
        #endif
    }

    template <class U>
    struct rebind{
        using other = Allocator<U, max_count>;
    };

    pointer allocate(size_t n) {
        pointer result = nullptr;


        if (free_count >= n && n != 0) {
            result = (pointer)free_blocks[free_count - n];
            free_count -= n;
        }

        #ifdef DEBUG
        std::cout << "I allocated\n";
        #endif
        
        return result;
    }

    void deallocate(pointer p, size_type n) {
        for(int i = 0; i < n; ++i) {
            free_blocks[free_count++] = p + i*sizeof(T*); 
        }
        #ifdef DEBUG
        std::cout << "I deallocated\n";
        #endif
    }

    template <typename U, typename... Args>
    void construct(U* p, Args &&...args) {
        
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }
};

}

#endif