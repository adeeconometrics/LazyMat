#ifndef __UTILS_H__
#define __UTILS_H__

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

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
auto make_matrix(const std::size_t row, const std::size_t col,
                 std::reference_wrapper<std::mt19937> prng)
    -> std::vector<std::vector<T>> {

  std::vector<std::vector<T>> result;
  result.reserve(row);

  for (std::size_t i = 0; i < row; i++) {
    std::vector<T> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, prng);
    result.emplace_back(row);
  }

  return result;
}

#endif // __UTILS_H__