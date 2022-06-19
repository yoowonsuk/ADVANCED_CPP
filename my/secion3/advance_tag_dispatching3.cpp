#include <iostream>
#include <vector>
#include <list>
#include <iterator> // advance

/* c++ 표준에 있음
// 1. empty class를 사용해서 반복자의 종류(category)를 타입화 한다
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {  };
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

// 2. 각 컨테이너의 반복자 설계시 해당 반복자가 어떤 종류(category) 인지
// 약속된 형태(iterator_category)로 외부에 알려준다.
template<typename T> class vector_iterator {
public:
	using iterator_category = random_access_iterator_tag; // c++ 11 이후, 덧셈
	typedef random_access_iterator_tag iterator_category;
};

template<typename T> class list_iterator {
public:
	using iterator_category = bidirectional_iterator_tag; // c++ 11 이후, 덧셈
	typedef bidirectional_iterator_tag iterator_category;
};
*/
/* 이것도 표준에 있음
template<typename T> struct iterator_traits {
	typedef typename T::iterator_category iterator_category;
};
// 부분 특수화
template<typename T> struct iterator_traits<T*> {
	typedef std::random_access_iterator_tag iterator_category; // + 되니까
};
*/

// 3. 반복자의 종류에 따라 다르게 동작하는 advance_imp() 함수 제공
template<typename T>
void advance_imp(T& it, typename std::iterator_traits<T>::difference_type sz, std::random_access_iterator_tag) {
	it = it + sz;
	std::cout << "using +" << std::endl;
}
template<typename T>
void advance_imp(T& it, typename std::iterator_traits<T>::difference_type sz, std::input_iterator_tag) {
	while (sz--)
		it++;
	std::cout << "using ++" << std::endl;
}

// 4. advance() 함수에서 전달된 반복자 안의 "iterator_category"에 따라
// 함수 오버로딩(tag dispatching) 기술 사용
template <typename T>
void xadvance(T& it, typename std::iterator_traits<T>::difference_type sz) { // 64비트 
	//advance_imp(it, sz, typename T::iterator_category());
	advance_imp(it, sz, typename std::iterator_traits<T>::iterator_category());
}


int main() {
	//std::vector<int> c = { 1, 2, 3, 4, 5,6 ,7 , 8, 9, 10 };
	//std::list<int> c = { 1, 2, 3, 4, 5,6 ,7 , 8, 9, 10 };
	int c[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // T : int* => error
	auto p = std::begin(c);

	//p = p + 5; // vector only
	//++p;++p;++p;++p;++p; // list, vector(성능 저하)
	xadvance(p, 5);

	std::cout << *p << std::endl;
}

// advance 구현방법 1. tag_dispatch(c++98) 2. enable_if(c++11) 3. if constexpr(c++17) 4. concept & requires clauses(c++20 이후)
// cppreference에서 bidirection 음수도 보기!
