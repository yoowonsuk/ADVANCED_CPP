#include <iostream>
#include <functional>
#include <type_traits>

using namespace std;

int main() {
  plus<int> f1;
  modulus<int> f2;

  int v = 0;
  auto f3 = [](int a, int b) { return a+b;};
  auto f4 = [v](int a, int b) { return a+b+v;};

  allocator<int> ax;

  cout << boolalpha;
  cout << is_empty_v< decltype(f1) > << endl;
  cout << is_empty_v< decltype(f2) > << endl;
  cout << is_empty_v< decltype(f3) > << endl;
  cout << is_empty_v< decltype(f4) > << endl;
  cout << is_empty_v< decltype(ax) > << endl;
}
