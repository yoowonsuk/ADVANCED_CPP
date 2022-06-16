#include <iostream>
#include <algorithm>
#include "default_delete.h"
#include "compressed_pair.h"

template <typename T, typename D = default_delete<T> > class unique_ptr {
//  T* pobj;
//  D del;
//  compressed_pair<D, pointer> cpair;
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

  pointer get() const { return cpair.getSecond(); }
  D& get_deleter() { return cpair.getFirst(); }
  const D& get_deleter() const { return cpair.getFirst(); }
  void swap(unique_ptr& up) {
    std::swap(cpair.getFirst(), up.cpair.getFirst());
    std::swap(cpair.getSecond(), up.cpair.getSecond());
  }
  explicit operator bool() const { return static_cast<bool>(cpair.getSecond() ); }
  pointer release() { return std::exchange(cpair.getSecond(), nullptr); }
  void reset(pointer ptr = nullptr) {
    pointer old = std::exchange(cpair.getSecond(), ptr);
    if(old)
      cpair.getFirst()(old);
  }
private:
  compressed_pair<D, pointer> cpair;
};

int main() {
  unique_ptr<int> p1(new int);
  unique_ptr<int> p2(new int);

  int*p = p1.get();
  default_delete<int> d1 = p1.get_deleter();

  p1.swap(p2);

  if( p1) {}

  p1.release();
  p2.reset(new int);
}
