#include "../include/utils.hpp"
#include <array>
#include <initializer_list>
#include <iostream>
#include <random>

using std::array;
using std::cout;
using std::initializer_list;
using std::mt19937;

template <typename T, std::size_t N, std::size_t M> class Matrix {
public:
  using iterator = typename array<array<T, N>, M>::iterator;
  using const_iterator = typename array<array<T, N>, M>::const_iterator;

public:
  Matrix() = default;
  Matrix(const array<array<T, N>, M> &t_data) : m_data(t_data) {}

  auto begin() noexcept -> iterator { return m_data.begin(); }
  auto end() noexcept -> iterator { return m_data.end(); }
  auto cbegin() const noexcept -> const_iterator { return m_data.cbegin(); }
  auto cend() const noexcept -> const_iterator { return m_data.cend(); }

  auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    return m_data[i][j];
  }

  auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    return m_data[i][j];
  }

  template <typename Expr>
  auto operator=(const Expr &expr) -> Matrix<T, N, M> & {
    for (std::size_t i = 0; i < M; i++) {
      for (std::size_t j = 0; j < N; j++) {
        m_data.at(i).at(j) = expr(i, j);
      }
    }
    return *this;
  }

private:
  array<array<T, N>, M> m_data;
};

template <typename T, std::size_t N, std::size_t M>
constexpr auto operator==(const Matrix<T, N, M> &lhs,
                          const Matrix<T, N, M> &rhs) -> bool {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T, std::size_t N, std::size_t M>
constexpr auto operator!=(const Matrix<T, N, M> &lhs,
                          const Matrix<T, N, M> &rhs) -> bool {
  return !(lhs == rhs);
}

template <typename Op, typename Lhs, typename Rhs> class BinaryExpr {
public:
  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const noexcept {
    return op(lhs(i, j), rhs(i, j));
  }

private:
  Lhs lhs;
  Rhs rhs;
  Op op;
};

template <typename Lhs, typename Rhs>
constexpr auto operator+(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::plus<>, Lhs, Rhs> {
  return BinaryExpr<std::plus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator-(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::minus<>, Lhs, Rhs> {
  return BinaryExpr<std::minus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator*(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::multiplies<>, Lhs, Rhs> {
  return BinaryExpr<std::multiplies<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator/(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::divides<>, Lhs, Rhs> {
  return BinaryExpr<std::divides<>, Lhs, Rhs>(lhs, rhs);
}

auto main() -> int {
  mt19937 rng_a(64);
  mt19937 rng_b(65);

  Matrix<int, 2048, 2048> A(make_matrix<int, 2048, 2048>(std::ref(rng_a)));
  Matrix<int, 2048, 2048> B(make_matrix<int, 2048, 2048>(std::ref(rng_b)));

  Matrix<int, 2048, 2048> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
}
