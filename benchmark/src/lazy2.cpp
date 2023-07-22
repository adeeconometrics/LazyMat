#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

class Timer {
public:
  Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

  ~Timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                        end_time - start_time)
                        .count();
    std::cout << "Elapsed time: " << duration << " microseconds" << std::endl;
  }

private:
  std::chrono::high_resolution_clock::time_point start_time;
};

template <typename T> class Matrix {
public:
  Matrix(std::size_t rows, std::size_t cols)
      : data(rows, vector<T>(cols)), row(rows), col(cols) {}

  Matrix(const std::vector<vector<T>> &t_data, std::size_t rows,
         std::size_t cols)
      : data(t_data), row(rows), col(cols) {}

  auto operator[](std::size_t row) noexcept -> vector<T> & { return data[row]; }

  auto operator[](std::size_t row) const -> const vector<T> & {
    return data[row];
  }

  auto operator()(const std::size_t i, const std::size_t j) const noexcept
      -> T {
    return data[i][j];
  }

  auto operator()(const std::size_t i, const std::size_t j) noexcept -> T & {
    return data[i][j];
  }
  auto rows() const noexcept -> std::size_t { return row; }
  auto cols() const noexcept -> std::size_t { return col; }

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

template <typename Lhs, typename Rhs>
auto operator+(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::plus<>, Lhs, Rhs> {
  return BinaryExpr<std::plus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
auto operator-(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::minus<>, Lhs, Rhs> {
  return BinaryExpr<std::minus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
auto operator*(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::multiplies<>, Lhs, Rhs> {
  return BinaryExpr<std::multiplies<>, Lhs, Rhs>(lhs, rhs);
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

template <typename T>
auto make_matrix(const std::size_t row, const std::size_t col,
                 std::reference_wrapper<std::mt19937> prng) -> Matrix<T> {

  vector<vector<T>> result;
  result.reserve(row);

  for (std::size_t i = 0; i < row; i++) {
    std::vector<T> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, prng);
    result.emplace_back(row);
  }

  return {result, row, col};
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  Matrix<int> A = make_matrix<int>(2048, 2048, std::ref(rng_a));
  Matrix<int> B = make_matrix<int>(2048, 2048, std::ref(rng_b));

  Matrix<int> C(2048, 2048);

  {
    Timer timer;
    C = A * B * B + A;
  }

  std::cout << "A: " << A.rows() << "x" << A.cols() << " dims\n";
  std::cout << "B: " << B.rows() << "x" << B.cols() << " dims\n";

  return 0;
}
