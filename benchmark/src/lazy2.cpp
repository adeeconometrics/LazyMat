#include "../include/utils.hpp"
#include <cmath>
#include <iostream>
#include <vector>

using std::vector;

template <typename T> class Matrix {
public:
  Matrix(std::size_t rows, std::size_t cols) : row(rows), col(cols) {}

  Matrix(const std::vector<vector<T>> &t_data, std::size_t rows,
         std::size_t cols)
      : data(t_data), row(rows), col(cols) {}

  auto operator[](std::size_t row) noexcept -> vector<T> & { return data[row]; }

  auto operator[](std::size_t row) const -> const vector<T> & {
    return data[row];
  }

  auto operator()(std::size_t i, std::size_t j) const noexcept -> T {
    return data[i][j];
  }

  auto operator()(std::size_t i, std::size_t j) noexcept -> T & {
    return data[i][j];
  }
  auto rows() const noexcept -> std::size_t { return row; }
  auto cols() const noexcept -> std::size_t { return col; }

  template <typename Expr> auto operator=(const Expr &expr) -> Matrix<T> & {
    vector<vector<T>> M;
    M.reserve(row);

    for (std::size_t i = 0; i < row; ++i) {
      std::vector<T> m_row;
      m_row.reserve(col);
      for (std::size_t j = 0; j < col; ++j) {
        m_row.emplace_back(expr(i, j));
      }
      M.emplace_back(std::move(m_row));
    }
    data = M;
    return *this;
  }

private:
  vector<vector<T>> data;
  std::size_t row;
  std::size_t col;
};

// Binary expression template
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

template <typename Op, typename Expr> class UnaryExpr {
public:
  UnaryExpr(const Expr &expr) : expr(expr) {}

  auto operator()(std::size_t i, std::size_t j) const { return op(expr(i, j)); }

private:
  Expr expr;
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

template <typename Expr>
auto operator-(const Expr &expr) -> UnaryExpr<std::negate<>, Expr> {
  return UnaryExpr<std::negate<>, Expr>(expr);
}

struct LogOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log(t);
  }
};

template <typename Expr> auto log(const Expr &expr) -> UnaryExpr<LogOp, Expr> {
  return UnaryExpr<LogOp, Expr>(expr);
}

// Print the matrix
template <typename T> void printMatrix(const Matrix<T> &matrix) {
  for (std::size_t i = 0; i < matrix.rows(); ++i) {
    for (std::size_t j = 0; j < matrix.cols(); ++j) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  Matrix<int> A =
      Matrix<int>{make_matrix<int>(2048, 2048, std::ref(rng_a)), 2048, 2048};
  Matrix<int> B =
      Matrix<int>{make_matrix<int>(2048, 2048, std::ref(rng_b)), 2048, 2048};

  Matrix<int> C(2048, 2048);
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
  return 0;
}
