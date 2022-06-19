#include <iostream>

class Buffer {
public:
	Buffer(std::size_t size) { std::cout << "Initialize Buffer" << std::endl; }
};

class Stream {
public:
	Stream(Buffer& buf) { std::cout << "stream'ctor user Buffer" << std::endl; }
};

class PipeBuffer {
protected:
	Buffer buffer{ 1024 };
};
class PipeStream : public PipeBuffer, public Stream {
	//Buffer buffer{1024};
	//Buffer buffer;
public:
	PipeStream() : /*buffer(1024),*/ Stream(buffer) {} // => PipeBuffer(), Stream(buffer) {}
};

int main() {
	//Buffer buf(1024);
	//Stream s(buf);

	PipeStream ps; // 초기화되지 않은 버퍼 사용
}
