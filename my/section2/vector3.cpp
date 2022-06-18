#include <iostream>
#include "point.h"

template<typename T> struct MyAlloc {
    T* allocate(std::size_t n) {
        T* p = static_cast<T*>(std::malloc(n * sizeof(T)));
        std::cout << "allocate" << std::endl;
        return p;
    }
    void deallocate(T* p, std::size_t n) noexcept {
        free(p);
        std::cout << "deallocate" << std::endl;
    }
    template<typename ... ARGS> void construct(T* p, ARGS&& ... args) {
        new(p) T(std::forward<ARGS>(args)...);
        std::cout << "MyAlloc construct" << std::endl;
    }
    void destroy(T* p) {
        p->~T();
        std::cout << "Myalloc destory" << std::endl;
    }
    using value_type = T;
};

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

int main() {
    //Vector<Point> v(20); // error, Point hasn't got default constructor
    Point pt(0, 0);
    //Vector<Point> v(10, pt);
    Vector<Point, MyAlloc<Point> > v(10, pt);
}
