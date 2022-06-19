#include <vector>
#include <iostream>
#include <ranges>

template<typename T> class drop_view : public std::ranges::view_interface<drop_view<T> > {
	T rng;
	std::size_t count;
public:
	drop_view() = default;
	drop_view(T r, std::size_t c) : rng(r), count(c) {}
	auto begin() { return rng.begin() + count; }
	auto end() { return rng.end(); }
};

template<typename T>
drop_view(T&& t, std::size_t)->drop_view< std::views::all_t<T> >;

int main() {
	std::vector v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::ranges::reverse_view rv(v);
	drop_view dv(rv, 3);

	for (auto e : dv)
		std::cout << e << ", ";
}
