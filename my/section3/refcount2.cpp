#include <iostream>

class Car {
	int speed = 0;
	int refcnt = 0;

public:
	void addRef() { refcnt++;}
	void release() {
		if (--refcnt == 0)
			delete this;
	}
protected: // 외부에서 소멸자 호출 못 함
	~Car() { std::cout << "~Car" << std::endl; }
};

int main() {
	Car* p1 = new Car;
	p1->addRef();

	Car* p2 = p1;
	p2->addRef();

	// delete p1; error

	/*
	Car c;
	c.release(); // heap 영역이 아닌 지역변수? error
	*/
	p2->release();
	p1->release();
}
