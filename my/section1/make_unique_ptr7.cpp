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

  // disable copy
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  // enable move
  unique_ptr(unique_ptr&& up) : cpair(one_and_variadic_arg_t{}, std::forward<D>(up.get_deleter()), up.release()) {}

  unique_ptr& operator=(unique_ptr&& up) {
    if(this!=std::addressof(up)) {
      reset(up.release()); // pointer
      cpair.getFirst()() = std::forward<D>(up.cpair.getFirst()); // deleter
    }
    return *this;
  }
private:
  compressed_pair<D, pointer> cpair;
};

int main() {
  unique_ptr<int> up1(new int);
  //unique_ptr<int> up2 = up1; // error
  unique_ptr<int> up3 = std::move(up1); // ok
}
