#include <vector>
#include <iostream>
#include <ranges>

int main() {
	std::vector v1 = { 1, 2, 3};
	std::vector v2 = { 6, 7, 8, 9, 10 };

	//std::vector<int>& r1 = v1;
	//std::vector<int>& r2 = v2;

	// std::reference_wrapper의 view 버전
	std::ranges::ref_view r1 = v1; // 이동 가능한 참조
	std::ranges::ref_view r2 = v2; // 내부적으로 포인터
	r1 = r2; // 1. 복사 2. r1 참조가 바뀐다. // 참조자는 이동 불가능, 한 번 초기화 끝 => 복사다.

	std::cout << v1.size() << std::endl; // 5 -> 3 by ref_view
	std::cout << v2.size() << std::endl;// 5
	std::cout << r1.size() << std::endl;// 5
	std::cout << r2.size() << std::endl;// 5

	// &r1.base() == &v1
}
