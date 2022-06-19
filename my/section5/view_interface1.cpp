#include <vector>
#include <iostream>
#include <ranges>
#include <concepts>

template <typename T>
class view_interface : public std::ranges::view_base {
	T& Cast() { return static_cast<T&>(*this); }
public:
	//int size() { return /*count;*/ static_cast<take_view*>(this)->end() - static_cast<take_view*>(this)->begin(); } take_view 인지 아닌지 모름
	//int size() { return /*count;*/ static_cast<T*>(this)->end() - static_cast<T*>(this)->begin(); }
	int size() { return Cast().end() - Cast().begin(); }
};

template<typename T> class take_view : public view_interface<take_view<T> > {
	//T& rng;
	//std::ranges::ref_view<T> rng;
	T rng;
	std::size_t count;
public:
	take_view() = default; // 사라진 조건
	take_view(T r, std::size_t c) : rng(r), count(c) {} // 자원소유X 새로운 시가(뷰, view) 제공

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
	// int size() const이어야 하지만 begin, end도 const 함수가 필요해서 여기서는 없애고 구현하자
	//int size() { return /*count;*/ end() - begin(); }
};
template <typename T> // template deduction
//take_view(T&& t, std::size_t)->take_view<std::remove_cvref_t<decltype(std::views::all(t)) > >;
take_view(T&& t, std::size_t)->take_view<std::views::all_t<T> >; // T를 결정짓는 것임

/*
template<typename T> auto all(T&& arg) {
	if constexpr (std::ranges::view<std::remove_cvref_t<T> >) { // 참조포함, const volatile reference 제거
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
*/
template<typename T> class reverse_view : public view_interface<reverse_view<T> > {
	T rng;
public:
	reverse_view() = default;
	reverse_view(T& r) : rng(r) {} // 자원소유X 새로운 시가(뷰, view) 제공

	auto begin() { return std::make_reverse_iterator(rng.end()); }
	auto end() { return std::make_reverse_iterator(rng.begin()); }
};
template<typename T>
reverse_view(T&&)->reverse_view<std::views::all_t<T> >;

int main() {
	std::vector v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	reverse_view rv(v);
	//take_view tv(rv, 2);
	//for (auto e : tv) // tv(reverse_view(v), 2)) 임시객체라서 error
	//	std::cout << e << std::endl;

	take_view tv1(v, 3); // ref_view<vector>를 멤버로 포함
	take_view tv2(rv, 3); // ref_view<reverse_view>가 아니라
	                      // rv( reverse_view )의 복사본을 멤버로 포함

	//std::ranges::ref_view r1(v);
	//std::ranges::ref_view r2(std::vector<int>{1, 2, 3}); // error ref_view has pointer but 임시 객체
		
	//auto a1 = all(v);
	//auto a2 = all(tv);

	std::cout << typeid(tv1).name() << std::endl;
	std::cout << typeid(tv2).name() << std::endl;

	for (auto e : take_view(reverse_view(v), 3))
		std::cout << e << std::endl;

	take_view tv(v, 3);
	std::cout << v.size() << std::endl; // 10
	std::cout << tv.size() << std::endl; // 3

	reverse_view rv1(v);
	std::cout << rv1.size() << std::endl; // 10
}

