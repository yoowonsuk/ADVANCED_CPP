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
public:
  explicit unique_ptr(T* p): pobj(p) {}

  ~unique_ptr() {
    if(pobj) {
      D del;
      del(pobj);
    }
  }

  T& operator*() const {return *pobj;}
  T* operator->() const {return pobj;}
};

int main() {
  unique_ptr<int> p1(new int);
  unique_ptr<int, Freer> p2(static_cast<int*>(malloc(sizeof(int)))); // free
//  unique_ptr<int> p2(static_cast<int*>(malloc(sizeof(int))), free); // overhead, shared_ptr use like this
                                                              
}
