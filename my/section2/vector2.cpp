#include <iostream>
#include "point.h"

template <typename T> class Vector {
  T* buff;
  std::size_t size;
  std::size_t capacity;

public:
  Vector(std::size_t sz, const T& value = T() ) : size(sz), capacity(sz) {
    //buff = new T[sz];
    buff = static_cast<Point*>(operator new(sizeof(Point)*sz)); // only memory allocate
    int i = 0;
    try {
      for(i = 0; i<sz; i++) {
       // c++ 17: new T, c++20: std::construct_at(new, T)   new is address, T is argument
       //  new(&buff[i]) T; // default constructor
       new(&buff[i]) T(value); // copy constructor!!
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
  ~Vector() { /*delete[] buff;*/ for(int j = size-1; j>=0; j--) buff[j].~T(); operator delete(buff); }
};

int main() {
  //Vector<Point> v(20); // error, Point hasn't got default constructor
  Point pt(0, 0);
  Vector<Point> v(10, pt);
}
