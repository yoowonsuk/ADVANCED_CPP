#include <vector>
#include <iostream>
#include <ranges>


template<typename T> class take_view {
	//T& rng;
	std::ranges::ref_view<T> rng;
	std::size_t count;
public:
	take_view(T& r, std::size_t c) : rng(r), count(c) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return rng.begin(); }
	auto end() { return rng.begin() + count; }
	/*
	take_view& operator=(const take_view& tv) {
		if (&tv == this) return *this;
		rng = tv.rng;
		count = tv.count;
		return *this;
	}
	*/
};

template<typename T> class reverse_view {
	T& rng;
public:
	reverse_view(T& r) : rng(r) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return rng.rbegin(); }
	auto end() { return rng.rend(); }
};
int main() {
	std::vector v1 = { 1, 2, 3, 4, 5 };
	std::vector v2 = { 6, 7, 8 };
	take_view tv1(v1, 3);
	take_view tv2(v2, 2);
	tv1 = tv2; // 멤버로 참조가 있어서 대입연산자를 만들어주지 않는다
	std::cout << v1.size() << std::endl << v2.size() << std::endl; // 5, 5
		
}

