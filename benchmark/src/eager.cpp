// contains baseline impl of eager matrix

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using std::vector;
using Mat = vector<vector<float>>;

auto operator+(const vector<float> &lhs, const vector<float> &rhs)
    -> vector<float> {
  vector<float> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::plus<>{});
  return result;
}

auto operator*(const vector<float> &lhs, const vector<float> &rhs)
    -> vector<float> {
  vector<float> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::multiplies<>{});
  return result;
}

auto operator+(const Mat &lhs, const Mat &rhs) -> Mat {
  Mat result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](const auto a, const auto b) { return a + b; });
  return result;
}

auto operator*(const Mat &lhs, const Mat &rhs) -> Mat {
  Mat result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](const auto a, const auto b) { return a * b; });
  return result;
}

auto make_matrix(std::size_t row, std::size_t col,
                 std::reference_wrapper<std::mt19937> rng) -> Mat {
  Mat result;
  result.reserve(row);
  for (std::size_t i = 0; i < row; i++) {
    std::vector<float> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, rng);
    result.emplace_back(row);
  }

  return result;
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  const auto A = make_matrix(2048, 2048, rng_a);
  const auto B = make_matrix(2048, 2048, rng_b);

  const auto D = (A * B) * (A + B);
  std::cout << "A: " << A.size() << "x" << A[0].size() << " dims\n";
  std::cout << "B: " << B.size() << "x" << B[0].size() << " dims\n";
}