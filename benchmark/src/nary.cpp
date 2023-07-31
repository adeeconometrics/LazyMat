#include "../include/utils.hpp"

#include <array>
#include <functional>
#include <initializer_list>
#include <random>
#include <stdexcept>
#include <type_traits>

template <typename T> struct is_array : std::false_type {};

template <typename T, std::size_t N>
struct is_array<std::array<T, N>> : std::true_type {};

template <typename operand>
auto subscript(const operand &v, const std::size_t index) {
  if constexpr (is_array<operand>::value) {
    return v[index];
  }
  return v;
}

template <typename T, std::size_t N> struct lazy_vector {

  lazy_vector(const std::array<T, N> &t_data) : m_data(t_data) {}

  template <typename Expr> auto operator=(Expr rhs) -> lazy_vector<T, N> & {
    for (std::size_t i = 0; i < N; i++) {
      m_data[i] = rhs[i];
    }
    return *this;
  }

private:
  std::array<T, N> m_data;
};

template <typename callable, typename... operands> class expr {
  std::tuple<operands const &...> m_args;
  callable m_fn;

public:
  expr(callable t_fn, const operands &... t_args)
      : m_args(t_args...), m_fn(t_fn) {}

  auto operator[](const std::size_t i) const noexcept {
    const auto call_at_index = [this, i](const operands &... a) {
      return m_fn(subscript(a, i)...);
    };
    return std::apply(call_at_index, m_args);
  }
};

template <typename Lhs, typename Rhs>
auto operator*(Lhs const &lhs, Rhs const &rhs) {
  return expr{[](const auto &l, const auto &r) { return l * r; }, lhs, rhs};
}

template <typename Lhs, typename Rhs>
auto operator+(Lhs const &lhs, Rhs const &rhs) {
  return expr{[](const auto &l, const auto &r) { return l + r; }, lhs, rhs};
}

template <typename Lhs, typename Rhs>
auto operator-(Lhs const &lhs, Rhs const &rhs) {
  return expr{[](const auto &l, const auto &r) { return l - r; }, lhs, rhs};
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  auto A = lazy_vector{make_vector<int, 256>(std::ref(rng_a))};
  auto B = lazy_vector{make_vector<int, 256>(std::ref(rng_b))};

  lazy_vector<int, 256> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
}