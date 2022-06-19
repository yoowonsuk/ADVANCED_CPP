#include <iostream>

class RefCountBase {
protected:
	mutable int refcnt = 0; // 상수멤버함수에서도 수정가능한 멤버 
public:
	void addRef() const { refcnt++; }
};

template<typename T>
class RefCount : public RefCountBase {
	//mutable int refcnt = 0; // 상수멤버함수에서도 수정가능한 멤버 

public:
	//void addRef() const { refcnt++; }
	void release() {}; // void release(RefCount* this)
	void release() const { // void release(const RefCount* this) -> T*, not const T*
		if (--refcnt == 0)
			//delete static_cast<T*>(this); error
			//delete static_cast<T*>(const_cast<RefCount*> (this)); work
			delete static_cast<const T*>(this);
	}
protected: // 외부에서 소멸자 호출 못 함
	// 가상함수 테이블 오버헤드
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck : public RefCount<Truck> {
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

// template 유사 코드 계속 찍어내는 오버헤드
class Car : public RefCount<Car> {};


int main() {
	const Truck* p1 = new Truck; // 상수 객체는 상수 함수만 호출 가능
	p1->addRef();
	p1->release();
}
