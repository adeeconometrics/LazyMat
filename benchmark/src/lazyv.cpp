#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <tuple>
#include <type_traits>
#include <vector>

using std::tuple;
using std::vector;

template <typename T> struct is_vector : std::false_type {};

template <typename T, typename Allocator>
struct is_vector<std::vector<T, Allocator>> : std::true_type {};

template <typename Op>
auto subscript(const Op &op, const std::size_t index) -> Op {
  if constexpr (is_vector<Op>::value) {
    return op[index];
  }
  return op;
}

template <typename Callable, typename... Op> class expr {
public:
  expr(Callable t_fn, const Op &... t_args) : m_fn(t_fn), m_args(t_args...) {}

  auto operator[](const std::size_t index) const noexcept {
    const auto call_at_index = [this, index](const Op &... a) {
      return m_fn(subscript(a, index)...);
    };
    return std::apply(call_at_index, m_args);
  }

private:
  std::tuple<const Op &...> m_args;
  Callable m_fn;
};

template <typename Lhs, typename Rhs>
auto operator*(const Lhs &lhs, const Rhs &rhs) {
  return expr{[](const auto &l, const auto &r) { return l * r; }, lhs, rhs};
}

template <typename Lhs, typename Rhs>
auto operator+(const Lhs &lhs, const Rhs &rhs) {
  return expr{[](const auto &l, const auto &r) { return l + r; }, lhs, rhs};
}

template <typename Lhs, typename Rhs>
auto operator-(const Lhs &lhs, const Rhs &rhs) {
  return expr{[](const auto &l, const auto &r) { return l - r; }, lhs, rhs};
}

template <typename Lhs, typename Rhs>
auto operator/(const Lhs &lhs, const Rhs &rhs) {
  return expr{[](const auto &l, const auto &r) { return l / r; }, lhs, rhs};
}

// template <typename T, typename Callable, typename... Op>
// auto operator=(const expr<Callable, Op...> &expr) -> vector<T> {}

template <typename T>
auto make_vector(const std::size_t size,
                 std::reference_wrapper<std::mt19937> prng) -> vector<T> {

  vector<T> result;
  result.reserve(size);
  std::generate_n(std::back_inserter(result), size, prng);
  return result;
}

template <typename T>
auto operator<<(std::ostream &os, const std::vector<T> &v) -> std::ostream & {
  os << "[";
  for (const auto i : v)
    os << i << " ";
  return os << "]\n";
}

auto main() -> int {
  std::mt19937 rng(10);
  const auto v = make_vector<int>(10, std::ref(rng));

  std::cout << v;

  return 0;
}