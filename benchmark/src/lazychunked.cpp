#include "../include/utils.hpp"
#include <array>
#include <initializer_list>
#include <iostream>
#include <random>

using std::cout;
using std::initializer_list;
using std::mt19937;
using std::vector;

/// @brief Matrix object. Write constructor for
/// std::initializer_list<std::initializer_list>
/// @tparam T
/// @tparam Row
/// @tparam Col
template <typename T, std::size_t Row, std::size_t Col> class Matrix {
public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

public:
  Matrix() {
    for (auto &page : m_data)
      page = std::array<T, chunk_size>{};
  }

  Matrix(const Matrix<T, Row, Col> &) = default;
  Matrix(Matrix<T, Row, Col> &&) = default;
  Matrix(std::initializer_list<std::initializer_list<T>> t_data)
      : Matrix(std::vector<T>(t_data.begin(), t_data.end())) {}

  Matrix(const std::vector<T> &t_data) {
    if (t_data.size() != Row * Col) {
      throw std::invalid_argument("Invalid vector dimensions for matrix");
    }
    const std::size_t pages = (Row * Col + chunk_size - 1) / chunk_size;
    for (std::size_t i = 0; i < pages; ++i) {
      std::copy(t_data.begin() + (i * chunk_size),
                t_data.begin() + (i * chunk_size + chunk_size),
                m_data[i].begin()); // handle error
    }
  }

  auto operator=(const Matrix<T, Row, Col> &lhs)
      -> Matrix<T, Row, Col> & = default;

  auto operator=(Matrix<T, Row, Col> &&lhs) -> Matrix<T, Row, Col> & = default;

  constexpr auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    const size_t page_index = i / chunk_size;
    const size_t row_in_page = i % chunk_size;
    return m_data.at(page_index)[row_in_page * Col + j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    const size_t page_index = i / chunk_size;
    const size_t row_in_page = i % chunk_size;
    return m_data[page_index][row_in_page * Col + j];
  }

  constexpr auto dims() const noexcept -> std::pair<std::size_t, std::size_t> {
    return std::make_pair(Row, Col);
  }
  constexpr auto row() const noexcept -> std::size_t { return Row; }
  constexpr auto col() const noexcept -> std::size_t { return Col; }

  template <typename Expr>
  constexpr auto operator=(const Expr &expr) -> Matrix<T, Row, Col> & {
    for (std::size_t i = 0; i < Col; ++i) {
      const size_t page_index = i / chunk_size;
      const size_t row_in_page = i % chunk_size;
      for (std::size_t j = 0; j < Row; ++j) {
        // Evaluate the expression and assign to the matrix
        m_data[page_index][row_in_page * Col + j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  static constexpr std::size_t chunk_size = 3;
  std::vector<std::array<T, chunk_size>> m_data{(Row * Col + chunk_size - 1) /
                                                chunk_size};
};

template <typename T, std::size_t N, std::size_t M>
constexpr auto operator==(const Matrix<T, N, M> &lhs,
                          const Matrix<T, N, M> &rhs) -> bool {
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = 0; j < M; ++j) {
      if (lhs(i, j) != rhs(i, j))
        return false;
    }
  }
  return true;
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

  Matrix<int, 3, 3> A{std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}};
  Matrix<int, 3, 3> B{std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}};
  Matrix<int, 3, 3> E{
      std::vector<int>{3, 20, 63, 144, 275, 468, 735, 1088, 1539}};

  Matrix<int, 3, 3> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
  if (C == E) {
    std::cout << "true";
  }
}
