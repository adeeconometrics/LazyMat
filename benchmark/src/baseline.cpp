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
    for (std::size_t i = 0; i < M; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        m_data[i][j] = expr(i, j);
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

template <typename T, std::size_t Row, std::size_t Col>
auto eval(const Matrix<T, Row, Col> &A, const Matrix<T, Row, Col> &B)
    -> Matrix<T, Row, Col> {

  Matrix<T, Row, Col> result{};
  for (size_t i = 0; i < Row; i++) {
    for (size_t j = 0; j < Col; j++) {
      result(i, j) = A(i, j) * B(i, j) * B(i, j) + A(i, j) * B(i, j) +
                     A(i, j) * A(i, j) * B(i, j);
    }
  }
  return result;
}

auto main() -> int {
  mt19937 rng_a(64);
  mt19937 rng_b(65);

  Matrix<int, 256, 256> A(make_matrix<int, 256, 256>(std::ref(rng_a)));
  Matrix<int, 256, 256> B(make_matrix<int, 256, 256>(std::ref(rng_b)));
  Matrix<int, 256, 256> C;
  {
    Timer t;
    C = eval(A, B);
  }
}
