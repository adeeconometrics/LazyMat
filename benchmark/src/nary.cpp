#include "../include/utils.hpp"

#include <array>
#include <functional>
#include <initializer_list>
#include <iostream>
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

// template <typename Fn, typename RType, typename ... Args>
// struct Callable {

//   auto operator()(const Args &... args) -> RType {

//   }
// };

template <typename RType, typename... Args> class expr {
  std::tuple<Args const &...> m_args;
  std::function<RType(Args...)> m_fn;

public:
  expr(std::function<RType(Args...)> t_fn, const Args &... t_args)
      : m_args(t_args...), m_fn(t_fn) {}

  auto operator()(std::size_t i) const noexcept -> RType {
    const auto call_at_index = [this, i](const Args &... a) {
      return m_fn(subscript(a, i)...);
    };
    return std::apply(call_at_index, m_args);
  }
  // template <typename T> auto operator[](std::size_t i) const noexcept ->
  // RType {
  //   const auto call_at_index = [this, i](const Args &... a) {
  //     return m_fn(subscript(a, i)...);
  //   };
  //   return expr{call_at_index, std::get<const Args &>(m_args)...};
  // }

  // template <typename T> operator T() const {
  //   return m_fn(std::get<const Args &>(m_args)...);
  // }
};

template <typename Lhs, typename Rhs>
constexpr auto operator*(Lhs const &lhs, Rhs const &rhs) {
  return expr{
      [](const auto &l, const auto &r) -> decltype(l * r) { return l * r; },
      lhs, rhs};
}

template <typename T, std::size_t N> struct lazy_vector {

  lazy_vector() = default;
  lazy_vector(const std::array<T, N> &t_data) : m_data(t_data) {}

  template <typename RType, typename... Args>
  auto operator=(expr<RType, Args...> rhs) -> lazy_vector<T, N> & {
    for (std::size_t i = 0; i < N; i++) {
      m_data[i] = rhs[i];
    }
    return *this;
  }

  auto operator[](std::size_t index) const noexcept -> T {
    return m_data[index];
  }

  auto operator[](std::size_t index) -> T { return m_data[index]; }

private:
  std::array<T, N> m_data{};
};

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  auto A = lazy_vector<int, 64>{make_vector<int, 64>(std::ref(rng_a))};
  auto B = lazy_vector<int, 64>{make_vector<int, 64>(std::ref(rng_b))};

  lazy_vector<int, 64> C{};
  {
    Timer t;
    C = A * B;
  }
}