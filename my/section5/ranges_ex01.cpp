#include <vector>
#include <iostream>

template<typename T> class take_view {
	T& rng;
	std::size_t count;
public:
	take_view(T& r, std::size_t c) : rng(r), count(c) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return rng.begin(); }
	auto end() { return rng.begin() + count; }
};

template<typename T> class reverse_view {
	T& rng;
public:
	reverse_view(T& r) : rng(r) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return rng.rbegin(); }
	auto end() { return rng.rend(); }
};
int main() {
	std::vector v = { 1, 2, 3, 4, 5 };

	/*
	take_view tv(v, 3);
	for (auto e : tv) {
		std::cout << e << std::endl;
	}
	*/
//	for(auto e: take_view(v, 3))
	for(auto e: reverse_view(v))
	//for(auto e: reverse_view(take_view(v, 3))) error
		std::cout << e << std::endl;
}
