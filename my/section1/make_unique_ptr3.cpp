#include <iostream>
#include "car.h"

struct Freer {
  void operator()(void *p) const {
    std::cout << "free" << std::endl;
    free(p);
  }
};

template<typename T> struct default_delete {
//struct default_delete {
  //void operato1r()(void *p) const {
  void operator()(T *p) const {
    
    std::cout << "delete" << std::endl;
    delete p;
  }
};

template <typename T, typename D = default_delete<T> > class unique_ptr {
  T* pobj;
  D del;
public:
  explicit unique_ptr(T* p): pobj(p) {}
  unique_ptr(T*p, const D& d) : pobj(p), del(d) {} // copy constructor
  unique_ptr(T*p, D&& d) : pobj(p), del(std::move(d)) {} // for move(rvalue)
  ~unique_ptr() {
    if(pobj) {
//      D del; // lambda doesn't have default contstructor before c++20
      del(pobj);
    }
  }

  T& operator*() const {return *pobj;}
  T* operator->() const {return pobj;}
};

int main() {
  unique_ptr<int> p1(new int);
  // need type, 
  //unique_ptr<int, [](int*p) {free(p);}> p2(static_cast<int*>(malloc(sizeof(int)))); // free
  // before c++ 20 lambda is not assessible sentence ... 20 works, 17 not available
  //unique_ptr<int, decltype([](int*p) {free(p);})> p2(static_cast<int*>(malloc(sizeof(int))));
  auto del = [](int*p) {free(p);};
  unique_ptr<int, decltype(del)> p2(static_cast<int*>(malloc(sizeof(int))), del);
  unique_ptr<int, decltype(del)> p2(static_cast<int*>(malloc(sizeof(int))), std::move(del));
                                                              
}
