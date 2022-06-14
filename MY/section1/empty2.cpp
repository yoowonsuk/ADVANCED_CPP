#include <iostream>
#include <type_traits>

using namespace std;
class E1 {};
struct E2 {};
union NE1 {};

class E3 {
  static int data;
public:
  E3() {}
  void func() {}
};
int E3::data = 0;

class NE2 {
  int data;
};

class NE3 {
  virtual void func() {}
};

class E4 : public E2{};
class NE4 : virtual public E2 {};
class NE5 {
  E1 e1;
};

int main() {
  cout << boolalpha;
  cout << is_empty_v<E1> << endl;
  cout << is_empty_v<E2> << endl;
  cout << is_empty_v<E3> << endl;
  cout << is_empty_v<E4> << endl;


  cout << is_empty_v<NE1> << endl;
  cout << is_empty_v<NE2> << endl;
  cout << is_empty_v<NE3> << endl;
  cout << is_empty_v<NE4> << endl;
  cout << is_empty_v<NE5> << endl;
}
