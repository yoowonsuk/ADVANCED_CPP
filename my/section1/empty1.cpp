#include <iostream>
#include <type_traits>

using namespace std;

class Empty {};

class NoEmpty {
	int data;
};

int main() {
  Empty e;

  cout << sizeof(Empty) << endl;
  cout << sizeof(NoEmpty) << endl;

  cout << boolalpha;
  cout << is_empty<Empty>::value << endl;
  cout << is_empty_v<Empty> << endl;
  cout << is_empty_v<NoEmpty> << endl;
}
