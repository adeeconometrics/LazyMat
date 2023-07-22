#ifndef __UTILS_H__
#define __UTILS_H__

#include "../include/LazyMatrix.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

namespace lm {

class Timer {
public:
  Timer() : start_time(std::chrono::high_resolution_clock::now()) {}
  ~Timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                        end_time - start_time)
                        .count();
    std::cout << "Elapsed time: " << duration << " microseconds\n";
  }

private:
  std::chrono::high_resolution_clock::time_point start_time;
};

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
auto make_matrix(std::size_t row, std::size_t col,
                 std::reference_wrapper<std::mt19937> prng) -> Matrix<T> {

  std::vector<std::vector<T>> result;
  result.reserve(row);

  for (std::size_t i = 0; i < row; i++) {
    std::vector<T> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, prng);
    result.emplace_back(row);
  }

  return {result, row, col};
}

template <typename T>
auto operator<<(std::ostream &os, const lm::Matrix<T> &matrix)
    -> std::ostream & {
  static_assert(std::is_arithmetic_v<T>,
                "template parameter must be of type arithmetic");

  if (matrix.empty()) {
    os << "[]" << std::endl;
    return os;
  }

  std::size_t max_width = 0;
  for (std::size_t i = 0; i < matrix.rows(); i++) {
    for (std::size_t j = 0; j < matrix.cols(); j++) {
      std::size_t width = std::to_string(matrix(i, j)).size();
      if (width > max_width) {
        max_width = width;
      }
    }
  }

  os << "[";
  for (std::size_t i = 0; i < matrix.size(); ++i) {
    if (i != 0) {
      os << " ";
    }
    os << "[";
    for (std::size_t j = 0; j < matrix[i].size(); ++j) {
      os << std::setw(max_width) << matrix[i][j];
      if (j != matrix[i].size() - 1) {
        os << ", ";
      }
    }
    os << "]";
    if (i != matrix.size() - 1) {
      os << '\n';
    }
  }
  return os << "]\n";
}

template <typename T>
auto operator<<(std::ostream &os, const std::vector<T> &v) -> std::ostream & {
  os << "[";
  for (const auto i : v) {
    os << i << " ";
  }
  return os << "]\n";
};

} // namespace lm

#endif // __UTILS_H__