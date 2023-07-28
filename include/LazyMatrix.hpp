#ifndef __LAZYMATRIX_H__
#define __LAZYMATRIX_H__

#include <algorithm>
#include <array>
#include <cassert>
#include <initializer_list>
#include <stdexcept>

namespace lm {

template <typename T, std::size_t Row, std::size_t Col> class Matrix {
public:
  using iterator = typename std::array<std::array<T, Row>, Col>::iterator;
  using const_iterator =
      typename std::array<std::array<T, Row>, Col>::const_iterator;

public:
  Matrix() = default;
  Matrix(const Matrix<T, Row, Col> &) = default;
  Matrix(Matrix<T, Row, Col> &&) = default;

  Matrix(std::initializer_list<std::initializer_list<T>> t_list) {
    auto row_iter = t_list.begin();
    for (std::size_t i = 0; i < Row; ++i) {
      if (row_iter == t_list.end()) {
        throw std::invalid_argument("Insufficient rows in initializer list");
      }
      if (row_iter->size() != Col) {
        throw std::invalid_argument("Invalid row size in initializer list");
      }

      std::copy(row_iter->begin(), row_iter->end(), m_data[i].begin());
      ++row_iter;
    }
    if (row_iter != t_list.end()) {
      throw std::invalid_argument("Excess rows in initializer list");
    }
  }

  Matrix(const std::array<std::array<T, Row>, Col> &t_data) : m_data(t_data) {}

  auto operator=(const Matrix<T, Row, Col> &lhs)
      -> Matrix<T, Row, Col> & = default;

  auto operator=(Matrix<T, Row, Col> &&lhs) -> Matrix<T, Row, Col> & = default;

  constexpr auto operator[](std::size_t index) -> std::array<T, Row> & {
    return m_data[index];
  }

  constexpr auto operator[](std::size_t index) const
      -> const std::array<T, Row> & {
    return m_data[index];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    return m_data[i][j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    return m_data[i][j];
  }

  constexpr auto size() -> std::size_t { return Row; }
  auto begin() noexcept -> iterator { return m_data.begin(); }
  auto end() noexcept -> iterator { return m_data.end(); }
  auto cbegin() const noexcept -> const_iterator { return m_data.cbegin(); }
  auto cend() const noexcept -> const_iterator { return m_data.cend(); }

  template <typename Expr>
  auto operator=(const Expr &expr) -> Matrix<T, Row, Col> & {
    for (std::size_t i = 0; i < Row; ++i) {
      for (std::size_t j = 0; j < Col; ++j) {
        // Evaluate the expression and assign to the matrix
        m_data[i][j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  std::array<std::array<T, Row>, Col> m_data;
};

template <typename T, std::size_t Row, std::size_t Col>
constexpr auto operator==(const Matrix<T, Row, Col> &lhs,
                          const Matrix<T, Row, Col> &rhs) -> bool {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr auto operator!=(const Matrix<T, Row, Col> &lhs,
                          const Matrix<T, Row, Col> &rhs) -> bool {
  return !(lhs == rhs);
}

} // namespace lm

#endif // __LAZYMATRIX_H__