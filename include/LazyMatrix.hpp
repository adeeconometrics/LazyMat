#ifndef __LAZYMATRIX_H__
#define __LAZYMATRIX_H__

#include <array>
#include <cassert>
#include <initializer_list>

namespace lm {

template <typename T, std::size_t Row, std::size_t Col> class Matrix {
public:
  using iterator = typename std::array<std::array<T, Row>, Col>::iterator;
  using const_iterator =
      typename std::array<std::array<T, Row>, Col>::const_iterator;

public:
  Matrix(std::initializer_list<std::initializer_list<T>> t_list)
      : data(std::array<std::array<T, Row>, Col>(t_list.begin(),
                                                 t_list.end())) {}

  Matrix(const std::array<std::array<T, Row>, Col> &t_data, std::size_t rows,
         std::size_t cols)
      : data(t_data) {}

  constexpr auto operator[](std::size_t index) -> std::array<T, Row> & {
    return data[index];
  }

  constexpr auto operator[](std::size_t index) const
      -> const std::array<T, Row> & {
    return data[index];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    return data[i][j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    return data[i][j];
  }

  auto begin() noexcept -> iterator { return data.begin(); }
  auto end() noexcept -> iterator { return data.end(); }
  auto cbegin() const noexcept -> const_iterator { return data.cbegin(); }
  auto cend() const noexcept -> const_iterator { return data.cend(); }

  template <typename Expr>
  auto operator=(const Expr &expr) -> Matrix<T, Row, Col> & {
    for (std::size_t i = 0; i < Row; ++i) {
      for (std::size_t j = 0; j < Col; ++j) {
        // Evaluate the expression and assign to the matrix
        data[i][j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  std::array<std::array<T, Row>, Col> data{};
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