#include <iostream>

template<typename T> class MyAlloc {
public:
	// allocate, deallocate 있다고 가정
	/*
	template<typename U> struct rebind {
		typedef MyAlloc<U> other;
	};
	*/
	using value_type = T;
};

template<typename T> void foo(T ax) {
	// 현재 T는 MyAlloc<bool>
	std::cout << typeid(ax).name() << std::endl;

	// MyAlloc<bool> => MyAlloc<int> 로 변경 : rebind
	// c++98 스타일
	//typename T::template rebind<int>::other ax2; // typename은 T를 위해, template은 <int>를 위해
	//std::cout << typeid(ax2).name() << std::endl;

	typename std::allocator_traits<T>::template rebind_alloc<int> ax3; // c++11 이후
	std::cout << typeid(ax3).name() << std::endl;
}

int main() {
	MyAlloc<bool> ax;
	//std::allocator<bool> ax; C++20포함 이후 error + MyAlloc에 rebind 있으면..
	foo(ax);
}
