#ifndef __LAZYMATRIX_H__
#define __LAZYMATRIX_H__

#include <cassert>
#include <initializer_list>
#include <vector>

namespace lm {
template <typename T> class Matrix {
public:
  using iterator = typename std::vector<std::vector<T>>::iterator;
  using const_iterator = typename std::vector<std::vector<T>>::const_iterator;

public:
  Matrix(std::size_t rows, std::size_t cols)
      : data(rows, std::vector<T>(cols)), row(rows), col(cols) {}

  Matrix(std::initializer_list<std::initializer_list<T>> t_list)
      : data(std::vector<std::vector<T>>(t_list.begin(), t_list.end())),
        row(t_list.size()), col(t_list.begin()->size()) {}

  Matrix(const std::vector<std::vector<T>> &t_data, std::size_t rows,
         std::size_t cols)
      : data(t_data), row(rows), col(cols) {}

  constexpr auto operator[](std::size_t index) -> std::vector<T> & {
    assert(row > index);
    return data[index];
  }

  constexpr auto operator[](std::size_t index) const -> const std::vector<T> & {
    assert(row > index);
    return data[index];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    return data[i][j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    return data[i][j];
  }

  constexpr auto size() const noexcept -> std::size_t { return row; }
  constexpr auto rows() const noexcept -> std::size_t { return row; }
  constexpr auto cols() const noexcept -> std::size_t { return col; }
  constexpr auto empty() const noexcept -> bool { return data.empty(); }

  auto begin() noexcept -> iterator { return data.begin(); }
  auto end() noexcept -> iterator { return data.end(); }
  auto cbegin() const noexcept -> const_iterator { return data.cbegin(); }
  auto cend() const noexcept -> const_iterator { return data.cend(); }

  template <typename Expr> auto operator=(const Expr &expr) -> Matrix<T> & {
    for (std::size_t i = 0; i < row; ++i) {
      for (std::size_t j = 0; j < col; ++j) {
        // Evaluate the expression and assign to the matrix
        data[i][j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  std::vector<std::vector<T>> data;
  std::size_t row;
  std::size_t col;
};

template <typename T>
constexpr auto operator==(const Matrix<T> &lhs, const Matrix<T> &rhs) -> bool {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T>
constexpr auto operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs) -> bool {
  return !(lhs == rhs);
}

} // namespace lm

#endif // __LAZYMATRIX_H__