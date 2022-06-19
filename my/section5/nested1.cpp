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
	std::ranges::ref_view<T> rng;
public:
	reverse_view(T& r) : rng(r) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return std::make_reverse_iterator(rng.end()); }
	auto end() { return std::make_reverse_iterator(rng.begin()); }
};
int main() {
	std::vector v = { 1, 2, 3, 4, 5 };
	for (auto e : reverse_view(v))
		std::cout << e << std::endl;

	std::ranges::ref_view r1(v);
	//std::ranges::ref_view r2(std::vector<int>{1, 2, 3}); // error ref_view has pointer but 임시 객체
		
}

