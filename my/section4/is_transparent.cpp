#include <iostream>
#include <string>
#include <string_view>
#include <set>

struct People {
	std::string name;
	int age;

	People(std::string name, int age) : name{ name }, age{ age } {}
};

struct PeopleCompare {
	bool operator()(const People& p1, const People& p2) const {
		return p1.name < p2.name;
	}
	bool operator()(const People& p1, std::string_view name) const { // c++17 string_view
		return p1.name < name;
	}
	bool operator()(std::string_view name, const People& p1) const { // c++17 string_view
		return name < p1.name;
	}
	using is_transparent = int; // 자료형 아무거나(int, void) c++14 
};

int main() {
	std::set<People, PeopleCompare> s; // set은 tree, 비교 or less 가능해야

	s.emplace("kim", 20);
	s.emplace("lee", 25);
	s.emplace("park", 40);
	s.emplace("choi", 30);

	//auto p = s.find({ "kim", 20 }); // People("kim", 20)
	 auto p = s.find("kim"); // error
	std::cout << p->name << std::endl;
	std::cout << p->age << std::endl;
}
