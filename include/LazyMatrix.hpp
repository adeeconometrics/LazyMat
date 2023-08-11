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

namespace lm {

template <typename T, std::size_t Row, std::size_t Col, typename = void>
class Matrix {
public:
  using iterator = typename std::array<T, Row * Col>::iterator;
  using const_iterator = typename std::array<T, Row * Col>::const_iterator;

public:
  Matrix(){};

  Matrix(const Matrix<T, Row, Col> &other) : m_data(other.m_data){};

  Matrix(Matrix<T, Row, Col> &&other) : m_data(std::move(other.m_data)){};

  Matrix(std::initializer_list<std::initializer_list<T>> t_list) {
    // rewrite implementation
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

  Matrix(const std::array<T, Row * Col> &t_data) : m_data(t_data) {}

  Matrix(const std::vector<T> &t_data) {
    // if (t_data.size() != Row * Col) {
    //   throw std::invalid_argument(
    //       "Incompatible size of the std::vector to Matrix.");
    // }
    std::copy(t_data.cbegin(), t_data.cend(), m_data.begin());
  }

  auto operator=(const Matrix<T, Row, Col> &lhs) noexcept
      -> Matrix<T, Row, Col> & {
    std::swap(m_data, lhs.m_data);
    return *this;
  };

  auto operator=(Matrix<T, Row, Col> &&lhs) -> Matrix<T, Row, Col> & {
    m_data = std::move(lhs.m_data);
    return *this;
  };

  constexpr auto operator[](std::size_t index) -> T & {
    return m_data.at(index);
  }

  constexpr auto operator[](std::size_t index) const -> const T & {
    return m_data[index];
  }

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
    for (std::size_t i = 0; i < Row; ++i) {
      for (std::size_t j = 0; j < Col; ++j) {
        // Evaluate the expression and assign to the matrix
        m_data[i * Col + j] = expr(i, j);
      }
    }
    return *this;
  }

private:
  std::array<T, Row * Col> m_data{};
};

template <typename T, std::size_t Row, std::size_t Col>
class Matrix<T, Row, Col, std::enable_if_t<(Row * Col) >= (256 * 256)>> {
public:
  using iterator = typename std::array<T, Row * Col>::iterator;
  using const_iterator = typename std::array<T, Row * Col>::const_iterator;

public:
  Matrix() {
    for (auto &page : m_data)
      page = std::array<T, chunk_size>{};
  }

  Matrix(const Matrix<T, Row, Col> &other) : m_data(other.m_data){};

  Matrix(Matrix<T, Row, Col> &&other) : m_data(std::move(other.m_data)){};

  Matrix(std::initializer_list<std::initializer_list<T>> t_data)
      : Matrix(std::vector<T>(flatten_initializer_list(t_data))) {}

  Matrix(const std::vector<T> &t_data) {
    // if (t_data.size() != (Row * Col)) {
    //   throw std::invalid_argument("Invalid vector dimensions for matrix");
    // }
    const std::size_t pages =
        (Row * Col + chunk_size - 1) / chunk_size; // accounts for surplus
    for (std::size_t i = 0; i < pages; ++i) {
      std::copy(t_data.begin() + (i * chunk_size),
                t_data.begin() + (i * chunk_size + chunk_size),
                m_data[i].begin()); // handle error
    }
  }

  auto operator=(const Matrix<T, Row, Col> &lhs) noexcept
      -> Matrix<T, Row, Col> & {
    std::swap(m_data, lhs.m_data);
    return *this;
  };

  auto operator=(Matrix<T, Row, Col> &&lhs) -> Matrix<T, Row, Col> & {
    m_data = std::move(lhs.m_data);
    return *this;
  };

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

  constexpr auto begin() noexcept -> iterator { return m_data[0].begin(); }

  constexpr auto end() noexcept -> iterator {
    auto last_chunk = (Row * Col) % chunk_size;
    if (last_chunk == 0)
      last_chunk = chunk_size;
    return m_data[(Row * Col) / chunk_size].begin() + last_chunk;
  }

  constexpr auto cbegin() const noexcept -> const_iterator {
    return m_data[0].cbegin();
  }

  constexpr auto cend() const noexcept -> const_iterator {
    auto last_chunk = (Row * Col) % chunk_size;
    if (last_chunk == 0)
      last_chunk = chunk_size;
    return m_data[(Row * Col) / chunk_size].cbegin() + last_chunk;
  }

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
  static auto flatten_initializer_list(
      std::initializer_list<std::initializer_list<T>> t_data)
      -> std::vector<T> {

    std::vector<T> flat_data;
    flat_data.reserve(Row * Col);

    for (const auto &row_list : t_data)
      flat_data.insert(flat_data.end(), row_list.begin(), row_list.end());
    return flat_data;
  }

private:
  static constexpr std::size_t chunk_size = 256;
  std::vector<std::array<T, chunk_size>> m_data{(Row * Col + chunk_size - 1) /
                                                chunk_size};
};

// add different mat types

} // namespace lm

#endif // __LAZYMATRIX_H__