#ifndef ALLOCATOR
#define ALLOCATOR

#include <vector>
#include <iostream>
#include <cstddef>
#include <utility>

namespace lab {

    template<class T, size_t N>
    class Allocator {

    private:
        std::vector<T> used_blocks;
        std::vector<T*> free_blocks;
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
        #ifdef DEBUG
            std::cout << "I destructed\n";
        #endif
        }

        template <class U>
        struct rebind{
            using other = Allocator<U, max_count>;
        };

        pointer allocate(size_t) {
            pointer result = nullptr;

            if(free_count > 0) {
                result = free_blocks[--free_count];
            }

        #ifdef DEBUG
            std::cout << "I allocated\n";
        #endif

            return result;
        }

        void deallocate(pointer p, size_type) {
            if (free_count < max_count) {
                free_blocks[free_count++] = p;
            } else {
                throw std::runtime_error("Attempt to deallocate more blocks than allocated");
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
            if (p) {
                p->~T();
            } else {
                throw std::invalid_argument("Attempt to destroy a null pointer");
            }
        }
    };

}

#endif