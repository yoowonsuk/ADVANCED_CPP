#include <vector>
#include <iostream>
#include <ranges>
#include <concepts>

template<typename T> class take_view : public std::ranges::view_base {
	//T& rng;
	std::ranges::ref_view<T> rng;
	std::size_t count;
public:
	take_view() = default; // 사라진 조건
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

// 수정 안 했음, 해야함
template<typename T> class reverse_view {
	std::ranges::ref_view<T> rng;
public:
	reverse_view(T& r) : rng(r) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return std::make_reverse_iterator(rng.end()); }
	auto end() { return std::make_reverse_iterator(rng.begin()); }
};

template<typename T> auto all(T&& arg) {
	if constexpr (std::ranges::view<std::remove_cvref_t<T> >) {
		std::cout << "view" << std::endl;
		// 복사본 반환
		return std::remove_cvref_t<T>(arg);
	}
	else {
		std::cout << "not view" << std::endl;
		// vector라면 ref_view<vector>
		return std::ranges::ref_view<std::remove_cvref_t<T> >(arg);
	}
}

int main() {
	std::vector v = { 1, 2, 3, 4, 5 };
	reverse_view rv(v);
	take_view tv(rv, 2);
	for (auto e : tv) // tv(reverse_view(v), 2)) 임시객체라서 error
		std::cout << e << std::endl;

	//take_view tv1(v, 3); // ref_view<vector>를 멤버로 포함
	//take_view tv2(rv, 3); // ref_view<reverse_view>가 아니라
	                      // rv( reverse_view )의 복사본을 멤버로 포함

	//std::ranges::ref_view r1(v);
	//std::ranges::ref_view r2(std::vector<int>{1, 2, 3}); // error ref_view has pointer but 임시 객체
		
	auto a1 = all(v);
	auto a2 = all(tv);

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;
}

