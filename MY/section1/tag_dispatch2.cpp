#include <mutex>
#include <new>

std::mutex m;

int main() {
  std::unique_lock uq(m, std::adopt_lock);
  std::unique_lock uq(m, std::defer_lock);
  std::unique_lock uq(m, std::try_to_lock);

  int *p1 = new int[10];
  delete[] p1;

  int *p2 = new(std::nothrow) int[10]; // fail, return 0
  delete[] p2;
}
