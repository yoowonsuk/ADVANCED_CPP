#include <iostream>
#include <string>
#include "compressed_pair.h"

int main() {
  int n1; // default initialization
  int n2{}; // value initialization, C++11, int n2{} same in member init only

  compressed_pair<int, int*> cp(zero_and_variadic_arg_t{} );

  std::cout<<cp.getFirst() << std::endl << cp.getSecond() << std::endl; // 0, 0

  compressed_pair<std::string, std::string> cp1(one_and_variadic_arg_t{}, "A", "B");
//  compressed_pair<std::string, std::string> cp2(cp1);
  compressed_pair<std::string, std::string> cp2(std::move(cp1)); // if not make move, copy constructor both together compiler support them

  std::cout<<cp1.getFirst()<<", "<<cp1.getSecond() << std::endl;
  std::cout<<cp2.getFirst()<<", "<<cp2.getSecond()<<std::endl;
}

