#include <iostream>

class Label {
	char* text;
	std::size_t size;
	int* ref;

public:
	Label(const char* s) : ref(new int(1)) {
		size = strlen(s);
		text = new char[size + 1];
		strcpy_s(text, size + 1, s);
		ref = new int(1);
	}
	Label(const Label& other) : text(other.text), size(other.size), ref(other.ref) {
		(*ref)++;
	}
	~Label() {
		if (--(*ref) == 0) {
			delete ref, text;
		}
	}
	char& operator[](int idx) {
		if (*ref > 1) {
			(*ref)--;

			ref = new int(1);
			char* temp = new char[size + 1];
			strcpy_s(temp, size + 1, text);
			text = temp;
		}			
		return text[idx];
	}
	void print() const { std::cout << text << std::endl; }
};

int main() {
	Label lb1("hello");
	Label lb2 = lb1;

	char c = lb1[0];
	lb1[0] = 'A';

	lb1.print();
	lb2.print();
}
