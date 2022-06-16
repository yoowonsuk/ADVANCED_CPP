#include <iostream>
#include <string>
#include <type_traits>

//class Empty final {}; // final means no inherit
class Empty {};

struct one_and_variadic_arg_t { explicit one_and_variadic_arg_t() = default; };
struct zero_and_variadic_arg_t { explicit zero_and_variadic_arg_t() = default; };

template<typename T1, typename T2> struct compressed_pair
{
  [[no_unique_address]] T1 first;
  [[no_unique_address]] T2 second;

  //constexpr use in compile time
  //nopexcept
  constexpr const T1& getFirst() const noexcept  { return first; }
  constexpr const T2& getSecond() const noexcept { return second; }
  constexpr T1& getFirst() noexcept { return first; }
  constexpr T2& getSecond() noexcept { return second; }

//  move not supported
//  compressed_pair(const T1& arg1, const T2& arg2): first(arg1), second(arg2) {}
  template<typename A1, typename ... A2>
    constexpr compressed_pair(one_and_variadic_arg_t, A1&& arg1, A2&& ... arg2) noexcept(
        std::conjunction_v<std::is_nothrow_constructible<T1, A1>, std::is_nothrow_constructible<T2, A2... > >) // not is_nothrow_contructible_v
        : first(std::forward<A1>(arg1)), second(std::forward<A2>(arg2)...) {}
 template<typename ... A2>
    constexpr compressed_pair( zero_and_variadic_arg_t, A2&& ... arg2) noexcept(
        std::conjunction_v<std::is_nothrow_default_constructible<T1>, std::is_nothrow_constructible<T2, A2... > >) // not is_nothrow_contructible_v
        : first(), second(std::forward<A2>(arg2)...) {}
};

int main() {
  compressed_pair<int, int> cp1(one_and_variadic_arg_t{}, 1, 1);
  compressed_pair<Empty, int> cp2(zero_and_variadic_arg_t{}, 1);
  compressed_pair<int, Empty> cp3(zero_and_variadic_arg_t{});
  compressed_pair<Empty, Empty> cp4(zero_and_variadic_arg_t{});

  std::cout << sizeof(cp1) << std::endl << \
  sizeof(cp2) << std::endl << \
  sizeof(cp3) << std::endl << \
  sizeof(cp4) << std::endl;
}
