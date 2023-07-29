// contains baseline impl of eager matrix

#include "../include/utils.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>

using std::array;

template <typename T, std::size_t Row, std::size_t Col>
using Mat = array<array<T, Row>, Col>;

template <typename T, std::size_t Row>
auto operator+(const array<T, Row> &lhs, const array<T, Row> &rhs)
    -> array<T, Row> {
  array<T, Row> result;

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result), std::plus<>{});
  return result;
}

template <typename T, std::size_t Row>
auto operator*(const array<T, Row> &lhs, const array<T, Row> &rhs)
    -> array<T, Row> {
  array<T, Row> result;

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result), std::multiplies<>{});
  return result;
}

template <typename T, std::size_t Row>
auto operator-(const array<T, Row> &lhs, const array<T, Row> &rhs)
    -> array<T, Row> {
  array<T, Row> result;

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result), std::minus<>{});
  return result;
}

template <typename T, std::size_t Row>
auto operator/(const array<T, Row> &lhs, const array<T, Row> &rhs)
    -> array<T, Row> {
  array<T, Row> result;

  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result), std::divides<>{});
  return result;
}

template <typename T, std::size_t Row, std::size_t Col>
auto operator+(const Mat<T, Row, Col> &lhs, const Mat<T, Row, Col> &rhs)
    -> Mat<T, Row, Col> {
  Mat<T, Row, Col> result;
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result),
                 [](const auto a, const auto b) { return a + b; });
  return result;
}

template <typename T, std::size_t Row, std::size_t Col>
auto operator-(const Mat<T, Row, Col> &lhs, const Mat<T, Row, Col> &rhs)
    -> Mat<T, Row, Col> {
  Mat<T, Row, Col> result;
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result),
                 [](const auto a, const auto b) { return a - b; });
  return result;
}

template <typename T, std::size_t Row, std::size_t Col>
auto operator*(const Mat<T, Row, Col> &lhs, const Mat<T, Row, Col> &rhs)
    -> Mat<T, Row, Col> {
  Mat<T, Row, Col> result;
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result),
                 [](const auto a, const auto b) { return a * b; });
  return result;
}

template <typename T, std::size_t Row, std::size_t Col>
auto operator/(const Mat<T, Row, Col> &lhs, const Mat<T, Row, Col> &rhs)
    -> Mat<T, Row, Col> {
  Mat<T, Row, Col> result;
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::begin(result),
                 [](const auto a, const auto b) { return a / b; });
  return result;
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  auto A = make_matrix<int, 256, 256>(std::ref(rng_a));
  auto B = make_matrix<int, 256, 256>(std::ref(rng_b));
  Mat<int, 256, 256> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
}