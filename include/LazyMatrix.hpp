#ifndef __LAZYMATRIX_H__
#define __LAZYMATRIX_H__

#include <algorithm>
#include <array>
#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

// #include <omp.h>

namespace lm {

template <typename T, std::size_t Rows, std::size_t Cols> class Matrix {
public:
  Matrix() { m_data.reserve(Rows * Cols); };
  Matrix(const std::vector<T> &data) : m_data(data) {
    if (data.size() != Rows * Cols) {
      throw std::runtime_error("Invalid matrix size");
    }
  }
  Matrix(std::initializer_list<std::initializer_list<T>> t_list) {
    for (const auto &row : t_list) {
      for (const auto &col : row) {
        m_data.push_back(col);
      }
    }
  }

  constexpr auto operator()(std::size_t i, std::size_t j) const -> T {
    return m_data[i * Cols + j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) -> T & {
    return m_data[i * Cols + j];
  }

  constexpr auto rows() const -> std::size_t { return Rows; }
  constexpr auto cols() const -> std::size_t { return Cols; }

  constexpr auto cbegin() const -> typename std::vector<T>::const_iterator {
    return m_data.cbegin();
  }
  constexpr auto cend() const -> typename std::vector<T>::const_iterator {
    return m_data.cend();
  }
  constexpr auto begin() -> typename std::vector<T>::iterator {
    return m_data.begin();
  }
  constexpr auto end() -> typename std::vector<T>::iterator {
    return m_data.end();
  }

  template <typename Expr> auto operator=(const Expr &expr) -> Matrix & {
    // #pragma omp parallel for
    for (std::size_t i = 0; i < Rows; i++) {
// #pragma omp simd
#pragma clang loop vectorize(enable)
      for (std::size_t j = 0; j < Cols; j++) {
        m_data[i * Cols + j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  std::vector<T> m_data;
};

// add different mat types

} // namespace lm

#endif // __LAZYMATRIX_H__
