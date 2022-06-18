#include <iostream>
#include "point.h"

template<typename T> struct MyAlloc {
  T* allocate(std::size_t n) {
    T *p = static_cast<T*>(std::malloc(n * sizeof(T)));
    std::cout << "allocate" << std::endl;
    return p;
  }
  void deallocate(T *p, std::size_t n) noexcept {
    free(p);
    std::cout << "deallocate" << std::endl;
  }
  template<typename ... ARGS> void construct(T *p, ARGS&& ... args) {
    new(p) T(std::forward<ARGS>(args)...);
    std::cout << "MyAlloc construct" << std::endl;
  }
  void destroy(T* p) {
    p->~T();
    std::cout << "Myalloc destory" <<std::endl;
  }
};

int main(void) {
  Point *p1 = new Point(1, 2);
  delete p1;

  //std::allocator<Point> ax;
  MyAlloc<Point> ax;

  Point *p2 = ax.allocate(1); // only memory allocate, not constructor

  // c++20 deprecated
  ax.construct(p2, 0, 0); // Point(0, 0)
  ax.destroy(p2); // only deconstructor

  ax.deallocate(p2, 1);
   // default, template constructor, value_type member, == operator and != operator  => 4 seperated by ,
}
