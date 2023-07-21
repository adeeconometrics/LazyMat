#include <algorithm>
#include <random>
#include <vector>

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
  add(const Mat<T> &lhs, const Mat<T> &rhs) : m_lhs(lhs), m_rhs(rhs) {}

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

template <typename T> auto eval() -> Mat<T>;

auto main() -> int {}