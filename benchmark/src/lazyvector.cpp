#include "../include/utils.hpp"
#include <array>
#include <initializer_list>
#include <iostream>
#include <random>

using std::cout;
using std::initializer_list;
using std::mt19937;
using std::vector;

template <typename T, std::size_t Row, std::size_t Col> class Matrix {
public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

public:
  Matrix() {
    m_data.resize(Row * Col); // Resize vector to the required size
    std::fill(m_data.begin(), m_data.end(),
              T()); // Initialize with default values
  }

  Matrix(const Matrix<T, Row, Col> &) = default;
  Matrix(Matrix<T, Row, Col> &&) = default;

  Matrix(std::initializer_list<std::initializer_list<T>> t_list) {
    if (t_list.size() != Row) {
      throw std::invalid_argument("Invalid number of rows in initializer list");
    }

    auto data_iter = m_data.begin();
    for (const auto &row_list : t_list) {
      if (row_list.size() != Col) {
        throw std::invalid_argument("Invalid row size in initializer list");
      }

      std::copy(row_list.begin(), row_list.end(), data_iter);
      data_iter += Col;
    }
  }

  Matrix(const std::vector<T> &t_data) : m_data(t_data) {
    if (t_data.size() != Row * Col) {
      throw std::invalid_argument("Invalid vector dimensions for matrix");
    }
  }

  auto operator=(const Matrix<T, Row, Col> &lhs)
      -> Matrix<T, Row, Col> & = default;

  auto operator=(Matrix<T, Row, Col> &&lhs) -> Matrix<T, Row, Col> & = default;

  constexpr auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    return m_data[i * Col + j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    return m_data[i * Col + j];
  }

  constexpr auto dims() const noexcept -> std::pair<std::size_t, std::size_t> {
    return std::make_pair(Row, Col);
  }
  constexpr auto row() const noexcept -> std::size_t { return Row; }
  constexpr auto col() const noexcept -> std::size_t { return Col; }

  auto begin() noexcept -> iterator { return m_data.begin(); }
  auto end() noexcept -> iterator { return m_data.end(); }
  auto cbegin() const noexcept -> const_iterator { return m_data.cbegin(); }
  auto cend() const noexcept -> const_iterator { return m_data.cend(); }

  template <typename Expr>
  auto operator=(const Expr &expr) -> Matrix<T, Row, Col> & {
    T *data_ptr = m_data.data(); // Pointer to the beginning of the data

    for (std::size_t j = 0; j < Col; ++j) {
      for (std::size_t i = 0; i < Row; ++i) {
        // Evaluate the expression and assign to the matrix
        data_ptr[i * Col + j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  std::vector<T> m_data;
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

template <typename T, std::size_t Row, std::size_t Col>
auto operator<<(std::ostream &os, const Matrix<T, Row, Col> &Mat)
    -> std::ostream & {
  for (size_t i = 0; i < Row; i++) {
    for (size_t j = 0; j < Col; j++) {
      os << Mat(i, j) << " ";
    }
    os << '\n';
  }
  return os << '\n';
}

auto main() -> int {
  mt19937 rng_a(64);
  mt19937 rng_b(65);

  Matrix<int, 256, 256> A(make_vmatrix<int, 256, 256>(std::ref(rng_a)));
  Matrix<int, 256, 256> B(make_vmatrix<int, 256, 256>(std::ref(rng_b)));

  Matrix<int, 256, 256> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
}
