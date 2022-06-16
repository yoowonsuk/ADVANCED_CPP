#include <iostream>
#include <memory> // for smartpointer

class Car {
public:
  ~Car() {std::cout << "~Car" << std::endl;}
  void Go() { std::cout << "Car Go" << std::endl;}
};

int main() {
//  std::unique_ptr<Car> p = new Car; copy constructor error
  std::unique_ptr<Car> p(new Car); // explicit constructor 
                                   
  p->Go();
  (*p).Go();

  // std::unique_ptr<Car> p1 = p; error
  std::unique_ptr<Car> p2 = std::move(p); // ok
                                          
  Car* cp = p2.get(); // not good for unique
  p2.reset();
}
