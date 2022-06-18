#include <iostream>
#include <algorithm>
#include "default_delete.h"
#include "compressed_pair.h"

template <typename T, typename D = default_delete<T> > class unique_ptr {
//  T* pobj;
//  D del;
//  compressed_pair<D, pointer> cpair;

// if T : int[], only default_delete can be used, using pointer = int[]* ???
public:

  using pointer = T*;
  using element_type = T;
  using deleter_type = D;
  unique_ptr() noexcept : cpair(zero_and_variadic_arg_t{}) {}
  unique_ptr(std::nullptr_t) noexcept : cpair(zero_and_variadic_arg_t{}) {} // value init, (zero~, 0) is same result

  explicit unique_ptr(pointer p) noexcept : cpair(zero_and_variadic_arg_t{}, p) {}
  unique_ptr(pointer p, const D& d) noexcept : cpair(one_and_variadic_arg_t{}, d, p) {}
  unique_ptr(pointer p, D&& d) noexcept : cpair(one_and_variadic_arg_t{}, d, std::move(p)) {}
  ~unique_ptr() noexcept {
    if(cpair.getSecond()) {
//      D del; // lambda doesn't have default contstructor before c++20
      cpair.getFirst()(cpair.getSecond());
    }
  }

  T& operator*() const noexcept {return *cpair.getSecond();}
  pointer operator->() const noexcept {return cpair.getSecond();}

  pointer get() const noexcept { return cpair.getSecond(); }
  D& get_deleter() noexcept { return cpair.getFirst(); }
  const D& get_deleter() const noexcept { return cpair.getFirst(); }
  void swap(unique_ptr& up) noexcept {
    std::swap(cpair.getFirst(), up.cpair.getFirst());
    std::swap(cpair.getSecond(), up.cpair.getSecond());
  }
  explicit operator bool() const noexcept { return static_cast<bool>(cpair.getSecond() ); }
  pointer release() noexcept { return std::exchange(cpair.getSecond(), nullptr); }
  void reset(pointer ptr = nullptr) noexcept {
    pointer old = std::exchange(cpair.getSecond(), ptr);
    if(old)
      cpair.getFirst()(old);
  }

  // disable copy
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  // enable move
  unique_ptr(unique_ptr&& up) noexcept : cpair(one_and_variadic_arg_t{}, std::forward<D>(up.get_deleter()), up.release()) {}

  unique_ptr& operator=(unique_ptr&& up) noexcept {
    if(this!=std::addressof(up)) {
      reset(up.release()); // pointer
      cpair.getFirst()() = std::forward<D>(up.cpair.getFirst()); // deleter
    }
    return *this;
  }

  template<typename T2, typename D2> // enable_if will be great
  unique_ptr(unique_ptr<T2, D2>&& up) noexcept : cpair(one_and_variadic_arg_t{}, std::forward<D2>(up.get_deleter()), up.release()) {}

  template<typename T2, typename D2>
  unique_ptr& operator=(unique_ptr<T2, D2>&& up) noexcept {
    if(this!=std::addressof(up)) {
      reset(up.release()); // pointer
      cpair.getFirst()() = std::forward<D2>(up.cpair.getFirst()); // deleter
    }
    return *this;
  }

private:
  compressed_pair<D, pointer> cpair;
};

template <typename T, typename D > class unique_ptr<T[], D> {
//  T* pobj;
//  D del;
//  compressed_pair<D, pointer> cpair;

// if T : int[], only default_delete can be used, using pointer = int[]* ???
public:

  using pointer = T*;
  using element_type = T;
  using deleter_type = D;
  unique_ptr() noexcept : cpair(zero_and_variadic_arg_t{}) {}
  unique_ptr(std::nullptr_t) noexcept : cpair(zero_and_variadic_arg_t{}) {} // value init, (zero~, 0) is same result

  explicit unique_ptr(pointer p) noexcept : cpair(zero_and_variadic_arg_t{}, p) {}
  unique_ptr(pointer p, const D& d) noexcept : cpair(one_and_variadic_arg_t{}, d, p) {}
  unique_ptr(pointer p, D&& d) noexcept : cpair(one_and_variadic_arg_t{}, d, std::move(p)) {}
  ~unique_ptr() noexcept {
    if(cpair.getSecond()) {
//      D del; // lambda doesn't have default contstructor before c++20
      cpair.getFirst()(cpair.getSecond());
    }
  }

  T& operator*() const noexcept {return *cpair.getSecond();}
  pointer operator->() const noexcept {return cpair.getSecond();}

  pointer get() const noexcept { return cpair.getSecond(); }
  D& get_deleter() noexcept { return cpair.getFirst(); }
  const D& get_deleter() const noexcept { return cpair.getFirst(); }
  void swap(unique_ptr& up) noexcept {
    std::swap(cpair.getFirst(), up.cpair.getFirst());
    std::swap(cpair.getSecond(), up.cpair.getSecond());
  }
  explicit operator bool() const noexcept { return static_cast<bool>(cpair.getSecond() ); }
  pointer release() noexcept { return std::exchange(cpair.getSecond(), nullptr); }
  void reset(pointer ptr = nullptr) noexcept {
    pointer old = std::exchange(cpair.getSecond(), ptr);
    if(old)
      cpair.getFirst()(old);
  }

  // disable copy
  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  // enable move
  unique_ptr(unique_ptr&& up) noexcept : cpair(one_and_variadic_arg_t{}, std::forward<D>(up.get_deleter()), up.release()) {}

  unique_ptr& operator=(unique_ptr&& up) noexcept {
    if(this!=std::addressof(up)) {
      reset(up.release()); // pointer
      cpair.getFirst()() = std::forward<D>(up.cpair.getFirst()); // deleter
    }
    return *this;
  }

  template<typename T2, typename D2> // enable_if will be great
  unique_ptr(unique_ptr<T2, D2>&& up) noexcept : cpair(one_and_variadic_arg_t{}, std::forward<D2>(up.get_deleter()), up.release()) {}

  template<typename T2, typename D2>
  unique_ptr& operator=(unique_ptr<T2, D2>&& up) noexcept {
    if(this!=std::addressof(up)) {
      reset(up.release()); // pointer
      cpair.getFirst()() = std::forward<D2>(up.cpair.getFirst()); // deleter
    }
    return *this;
  }

private:
  compressed_pair<D, pointer> cpair;
};


class Animal {};
class Dog : public Animal {};

int main() {
  unique_ptr<int> up1(new int);
  //unique_ptr<int, ArrayDelete > up2(new int[10]);
  unique_ptr<int[]> up2(new int[10]);
}
