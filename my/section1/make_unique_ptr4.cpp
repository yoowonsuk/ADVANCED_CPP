#include <iostream>
#include "default_delete.h"
#include "compressed_pair.h"

template <typename T, typename D = default_delete<T> > class unique_ptr {
//  T* pobj;
//  D del;
  compressed_pair<D, T*> cpair;
public:
  explicit unique_ptr(T* p): cpair(zero_and_variadic_arg_t{}, p) {}
  unique_ptr(T*p, const D& d) : cpair(one_and_variadic_arg_t{}, d, p) {}
  unique_ptr(T*p, D&& d) : cpair(one_and_variadic_arg_t{}, d, std::move(p)) {}
  ~unique_ptr() {
    if(cpair.getSecond()) {
//      D del; // lambda doesn't have default contstructor before c++20
      cpair.getFirst()(cpair.getSecond());
    }
  }

  T& operator*() const {return *cpair.getSecond();}
  T* operator->() const {return cpair.getSecond();}
};

int main() {
  unique_ptr<int> p1(new int);
  // need type, 
  //unique_ptr<int, [](int*p) {free(p);}> p2(static_cast<int*>(malloc(sizeof(int)))); // free
  // before c++ 20 lambda is not assessible sentence ... 20 works, 17 not available
  //unique_ptr<int, decltype([](int*p) {free(p);})> p2(static_cast<int*>(malloc(sizeof(int))));
  auto del = [](int*p) {free(p);};
  unique_ptr<int, decltype(del)> p2(static_cast<int*>(malloc(sizeof(int))), del);
  //unique_ptr<int, decltype(del)> p2(static_cast<int*>(malloc(sizeof(int))), std::move(del));
                                                              
  std::cout << sizeof(p1) << std::endl << sizeof(p2);
}
