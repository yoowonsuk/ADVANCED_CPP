#pragma once 
#include <iostream>

template<typename T> struct default_delete {
//struct default_delete {
  //void operato1r()(void *p) const {
  default_delete() = default;
  template<typename U> default_delete(const default_delete<U>&) {} // dog, animal 

  void operator()(T *p) const {
    
    std::cout << "delete" << std::endl;
    delete p;
  }
};

// template specialization
template<typename T> struct default_delete<T[]> {
//struct default_delete {
  //void operato1r()(void *p) const {
  default_delete() = default;
  template<typename U> default_delete(const default_delete<U>&) {} // dog, animal 

  void operator()(T *p) const {
    
    std::cout << "delete" << std::endl;
    delete[] p;
  }
};

