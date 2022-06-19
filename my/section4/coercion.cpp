#include <type_traits>

class Animal {};
class Dog : public Animal {};

template<typename T> class smartptr {
	T* ptr = nullptr;
public:
	smartptr() = default;
	smartptr(T* p) : ptr(p) {};

	// 소멸자 , 참조계수(refcount) 기법 등

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*> > >
	smartptr(const smartptr<U>& sp) : ptr(sp.ptr) {} // 다른 타입 private 접근 불가

	template<typename T> friend class smartptr;
	// template<typename> friend class smartptr; smartptr은 템플릿 클래스인데 나랑 친구다
};

int main() {
	//smartptr<int> sp(new int);
	Dog* p1 = new Dog;
	Animal* p2 = p1;

	smartptr<Dog> sp1(new Dog); // = new Dog 보다 이런식으로 많이 적음
	smartptr<Animal> sp2 = sp1; // 다른 타입 -> 복사생성자 호출 안 됨

	smartptr<int> sp3(new int);
	smartptr<double> sp4 = sp3; // error 템플릿 복사생성자에서..
}
