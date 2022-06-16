#include <iostream>
#include "default_delete.h"
#include "compressed_pair.h"

template <typename T, typename D = default_delete<T> > class unique_ptr {
//  T* pobj;
//  D del;
  //compressed_pair<D, pointer> cpair;
public:

  using pointer = T*;
  using element_type = T;
  using deleter_type = D;
  unique_ptr() : cpair(zero_and_variadic_arg_t{}) {}
  unique_ptr(std::nullptr_t) : cpair(zero_and_variadic_arg_t{}) {} // value init, (zero~, 0) is same result

  explicit unique_ptr(pointer p): cpair(zero_and_variadic_arg_t{}, p) {}
  unique_ptr(pointer p, const D& d) : cpair(one_and_variadic_arg_t{}, d, p) {}
  unique_ptr(pointer p, D&& d) : cpair(one_and_variadic_arg_t{}, d, std::move(p)) {}
  ~unique_ptr() {
    if(cpair.getSecond()) {
//      D del; // lambda doesn't have default contstructor before c++20
      cpair.getFirst()(cpair.getSecond());
    }
  }

  T& operator*() const {return *cpair.getSecond();}
  pointer operator->() const {return cpair.getSecond();}
private:
  compressed_pair<D, pointer> cpair;
};

int main() {
  unique_ptr<int> p1; // default
  unique_ptr<int> p2(nullptr); // null init, not explicit for copy constructor
  unique_ptr<int> p3 = nullptr;

  unique_ptr<int>::element_type n; // int n
  unique_ptr<int>::deleter_type d; // default_delete<int> d
  unique_ptr<int>::pointer p;      // int* p
}
