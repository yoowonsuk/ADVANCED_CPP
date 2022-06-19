#include <iostream>
#include <atomic>
#include <memory>

class Truck {
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

int main() {
	std::shared_ptr<Truck> sp1(new Truck);
	std::shared_ptr<Truck> sp2 = sp1;

	// 관리 객체가 2개 이상 생성, std::make_shared 이용하자!
	Truck* p1 = new Truck;
	std::shared_ptr<Truck> sp3(p1);
	std::shared_ptr<Truck> sp4(p1); // sp3가 아니라.. 처음 온 주소라고 생각


}
