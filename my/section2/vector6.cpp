#include <iostream>
#include "point.h"

template <typename T, typename Alloc = std::allocator<T> > class Vector {
    T* buff;
    std::size_t size;
    std::size_t capacity;

    Alloc ax;
public:
    Vector(std::size_t sz, const T& value = T()) : size(sz), capacity(sz) {
        //buff = new T[sz];
        //buff = static_cast<Point*>(operator new(sizeof(Point) * sz)); // only memory allocate
        buff = std::allocator_traits<Alloc>::allocate(ax, sizeof(T) * sz);
        int i = 0;
        try {
            for (i = 0; i < sz; i++) {
                // c++ 17: new T, c++20: std::construct_at(new, T)   new is address, T is argument
                //  new(&buff[i]) T; // default constructor
                new(&buff[i]) T(value); // copy constructor!!
                std::allocator_traits<Alloc>::construct(ax, &buff[i], value);
            }
        }
        catch (...) {
            for (int j = i - 1; j >= 0; j--)
                //buff[j].~T(); // or std::destroy_at(address)
                std::allocator_traits<Alloc>::destroy(ax, &buff[i]);

            operator delete(buff);
            std::allocator_traits<Alloc>::deallocate(ax, buff, capacity);
            size = capacity = 0;
            throw; // present message
        }
    }
    /* default constructor
    Vector(std::size_t sz) : size(sz), capacity(sz) {
       //buff = new T[sz];
       buff = static_cast<Point*>(operator new(sizeof(Point)*sz)); // only memory allocate
       int i = 0;
       try {
         for(i = 0; i<sz; i++) {
          // c++ 17: new T, c++20: std::construct_at(new, T)   new is address, T is argument
            new(&buff[i]) T; // default constructor
      //    new(&buff[i]) T(value); // copy constructor!!
         }
       }
       catch(...) {
         for(int j = i-1; j>=0; j--)
           buff[j].~T(); // or std::destroy_at(address)
       operator delete(buff);
       size = capacity = 0;
       throw; // present message
       }
     }
     */
    ~Vector() { /*delete[] buff;*/ for (int j = size - 1; j >= 0; j--) /*buff[j].~T(); operator delete(buff); */
        std::allocator_traits<Alloc>::destroy(ax, &buff[j]);

    std::allocator_traits<Alloc>::deallocate(ax, buff, capacity);
    }
};

// vector<bool>
template <typename Alloc> class Vector<bool, Alloc> {
    int* buff;
    std::size_t size;
    std::size_t capacity;

    //Alloc ax;

    // typename std::allocator_traits<Alloc>::template rebind_alloc<int> ax;
    using Alloc2 = typename std::allocator_traits<Alloc>::template rebind_alloc<int>;
    Alloc2 ax;
public:
    Vector(std::size_t sz, const bool value = false) : size(sz), capacity(sz) {
        //buff = new T[sz];
        //buff = static_cast<Point*>(operator new(sizeof(Point) * sz)); // only memory allocate
        //buff = std::allocator_traits<Alloc>::allocate(ax, sizeof(T) * sz);

        // sz bit 만큼 할당... new int[sz/sizeof(int)]
        // ax => std::allocator<bool> => std::allocator<int>
        buff = std::allocator_traits<Alloc2>::allocate(ax, sz / sizeof(int) + 1);
       
        // buff 비트 초기화
    }
    /* default constructor
    Vector(std::size_t sz) : size(sz), capacity(sz) {
       //buff = new T[sz];
       buff = static_cast<Point*>(operator new(sizeof(Point)*sz)); // only memory allocate
       int i = 0;
       try {
         for(i = 0; i<sz; i++) {
          // c++ 17: new T, c++20: std::construct_at(new, T)   new is address, T is argument
            new(&buff[i]) T; // default constructor
      //    new(&buff[i]) T(value); // copy constructor!!
         }
       }
       catch(...) {
         for(int j = i-1; j>=0; j--)
           buff[j].~T(); // or std::destroy_at(address)
       operator delete(buff);
       size = capacity = 0;
       throw; // present message
       }
     }
     */
    ~Vector() { 

    std::allocator_traits<Alloc2>::deallocate(ax, buff, capacity);
    }
};

int main() {
    Vector<int> v1(100, 3);
    Vector<bool> v2(100, false);
}
