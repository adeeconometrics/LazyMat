// contains baseline impl of eager matrix

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

template <typename T> using Mat = vector<vector<T>>;

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

template <typename T>
constexpr auto operator+(const vector<T> &lhs, const vector<T> &rhs)
    -> vector<T> {
  vector<T> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::plus<>{});
  return result;
}

template <typename T>
constexpr auto operator*(const vector<T> &lhs, const vector<T> &rhs)
    -> vector<T> {
  vector<T> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::multiplies<>{});
  return result;
}

template <typename T>
constexpr auto operator+(const Mat<T> &lhs, const Mat<T> &rhs) -> Mat<T> {
  Mat<T> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](const auto a, const auto b) { return a + b; });
  return result;
}

template <typename T>
constexpr auto operator*(const Mat<T> &lhs, const Mat<T> &rhs) -> Mat<T> {
  Mat<T> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result),
                 [](const auto a, const auto b) { return a * b; });
  return result;
}

template <typename T>
auto make_matrix(std::size_t row, std::size_t col,
                 std::reference_wrapper<std::mt19937> rng) -> Mat<T> {
  Mat<T> result;
  result.reserve(row);
  for (std::size_t i = 0; i < row; i++) {
    std::vector<T> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, rng);
    result.emplace_back(row);
  }

  return result;
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  const auto A = make_matrix<int>(2048, 2048, rng_a);
  const auto B = make_matrix<int>(2048, 2048, rng_b);
  const auto D = A * B * B + A * B + A * A * B;
}