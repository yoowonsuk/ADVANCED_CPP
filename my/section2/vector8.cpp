#include <iostream>
#include <vector>

int main() {
	std::vector<int> vi(10);
	std::vector<bool> vb(10);

	auto a1 = vi[0];
	auto a2 = vb[0];

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;

	for(auto& e : vi)
		std::cout << e << std::endl;

	//for (auto e : vb) // rvalue -> for(const auto& e: vb) or for(auto&& e: vb) with forwarding reference
	for (auto&& e : vb)
		std::cout << e << std::endl;
}
