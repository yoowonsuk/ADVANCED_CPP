#include <iostream>
#include <vector>
#include <list>
#include <iterator> // advance

int main() {
	//std::vector<int> c = { 1, 2, 3, 4, 5,6 ,7 , 8, 9, 10 };
	std::list<int> c = { 1, 2, 3, 4, 5,6 ,7 , 8, 9, 10 };

	auto p = std::begin(c);

	//p = p + 5; // vector only
	//++p;++p;++p;++p;++p; // list, vector(성능 저하)
	std::advance(p, 5);

	std::cout << *p << std::endl;
}

// advance 구현방법 1. tag_dispatch(c++98) 2. enable_if(c++11) 3. if constexpr(c++17) 4. concept & requires clauses(c++20 이후)
