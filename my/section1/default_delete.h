#pragma once 
#include <iostream>

template<typename T> struct default_delete {
//struct default_delete {
  //void operato1r()(void *p) const {
  void operator()(T *p) const {
    
    std::cout << "delete" << std::endl;
    delete p;
  }
};

