#include <memory> // for smart pointer

int main() {
	auto del = [](void* p) { free(p); };
	std::unique_ptr<int, decltype(del)> up1(static_cast<int*>(malloc(sizeof(int) * 20)), del);

	//std::unique_ptr<int> up1(static_cast<int*>(malloc(sizeof(int) * 20)));
}
