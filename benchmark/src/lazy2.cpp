#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
// Write a matrix class to store size in std::pair

using std::vector;

template <typename T> using Mat = vector<vector<T>>;

template <typename T>
auto make_matrix(std::size_t row, std::size_t col,
                 std::reference_wrapper<std::mt19937> rng) -> Mat<T> {
  Mat<T> result;
  result.reserve(row);
  for (std::size_t i = 0; i < row; i++) {
    std::vector<float> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, rng);
    result.emplace_back(row);
  }

  return result;
}

template <typename T> struct add {
  add(const Mat<T> &lhs, const Mat<T> &rhs) : m_lhs(lhs), m_rhs(rhs) {
    // perform assersions on Mat size rhs.size() == lhs.size()
  }

  auto operator()(std::size_t row, std::size_t col) const noexcept -> T {
    return m_lhs[row][col] + m_rhs[col][col];
  }

private:
  Mat<T> m_lhs;
  Mat<T> m_rhs;
};

template <typename T> struct mul {
  mul(const Mat<T> &lhs, const Mat<T> &rhs) : m_lhs(lhs), m_rhs(rhs) {}

  auto operator()(std::size_t row, std::size_t col) const noexcept -> T {
    return m_lhs[row][col] * m_rhs[col][col];
  }

private:
  Mat<T> m_lhs;
  Mat<T> m_rhs;
};

template <typename T>
auto operator+(const Mat<T> &lhs, const Mat<T> &rhs) -> add<T> {
  return add(lhs, rhs);
}

template <typename T> auto eval(const add<T> &expr) -> Mat<T> {
  Mat<T> result;

  return result;
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  const auto A = make_matrix<float>(2048, 2048, rng_a);
  const auto B = make_matrix<float>(2048, 2048, rng_b);

  auto C = A + A + B + A + B + B;

  std::cout << "A: " << A.size() << "x" << A[0].size() << " dims\n";
  std::cout << "B: " << B.size() << "x" << B[0].size() << " dims\n";
}