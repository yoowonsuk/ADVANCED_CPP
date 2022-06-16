#include <iostream>
#include "car.h"

template <typename T> class unique_ptr {
  T* pobj;
public:
  explicit unique_ptr(T* p): pobj(p) {}

  ~unique_ptr() {
    if(pobj)
      delete pobj;
  }

  T& operator*() const {return *pobj;}
  T* operator->() const {return pobj;}
};

int main() {
  // unique_ptr<Car> p1 = new Car; error (because of explicit)
  const unique_ptr<Car> p2(new Car); // ok and const unique~ -> should make operator const


  p2->Go();
  (*p2).Go();
}
