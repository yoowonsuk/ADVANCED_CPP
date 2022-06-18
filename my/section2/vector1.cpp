#include <iostream>
#include "point.h"

template <typename T> class Vector {
  T* buff;
  std::size_t size;
  std::size_t capacity;

public:
  Vector(std::size_t sz) : size(sz), capacity(sz) {
    //buff = new T[sz];
    buff = static_cast<Point*>(operator new(sizeof(Point)*sz)); // only memory allocate
  }
  ~Vector() { /*delete[] buff;*/ operator delete(buff); }
};

int main() {
  Vector<Point> v(20); // error, Point hasn't got default constructor
}
