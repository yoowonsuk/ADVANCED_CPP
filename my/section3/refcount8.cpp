#include <iostream>
#include <atomic>

class RefCountBase {
protected:
	mutable std::atomic<int> refcnt{ 0 }; // 상수멤버함수에서도 수정가능한 멤버 
	// atomic 쓰레드에 안전한 변수
public:
	//void addRef() const { refcnt++; } // refcnt.fetch_add(1, std::memory_order_seq_cst); memory reordering도 막음
	void addRef() const { refcnt.fetch_add(1, std::memory_order_relaxed); }
};

template<typename T>
class RefCount : public RefCountBase {
	//mutable int refcnt = 0; // 상수멤버함수에서도 수정가능한 멤버 

public:
	//void addRef() const { refcnt++; }
	void release() {}; // void release(RefCount* this)
	void release() const { // void release(const RefCount* this) -> T*, not const T*
		int ret = refcnt.fetch_sub(1, std::memory_order_acq_rel);
		if(ret == 1)
		//if (--refcnt == 0)
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

template<typename T> class AutoPtr {
	T* obj;
public:
	explicit AutoPtr(T* p = nullptr) : obj(p) { if (obj) obj->addRef(); };
	AutoPtr(const AutoPtr<T>& ap) : obj(ap.obj) { if (obj) obj->addRef(); }
	~AutoPtr() { if (obj) obj->release(); }
};

int main() {

	AutoPtr<Truck> p1(new Truck);
	AutoPtr<Truck> p2 = p1;

	/*
	Truck* p1 = new Truck; // 객체는 생성자, 포인터는X => smart_pointer
	p1->addRef();
	Truck* p2 = p1;
	p2->addRef();

	p2->release();
	p1->release();
	*/
}
