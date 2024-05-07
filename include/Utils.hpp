#ifndef __UTILS_H__
#define __UTILS_H__

#include "../include/LazyMatrix.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <type_traits>

namespace lm {

/**
 * @brief Serves as a simple timer utility used for benchmarking performance.
 *
 */
class Timer {
public:
  /**
   * @brief Construct a new Timer object
   *
   */
  explicit Timer()
      : start_time(std::chrono::high_resolution_clock::now()), m_iterations(1) {
  }
  /**
   * @brief Construct a new Timer object
   *
   * @param t_iterations specifies the number of iterations
   */
  explicit Timer(std::size_t t_iterations) : m_iterations(t_iterations) {}

  ~Timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              end_time - start_time)
                              .count();
    auto mean_duration = total_duration / m_iterations;
    std::cout << "Mean elapsed time: " << mean_duration << " ns" << std::endl;
  }
  /**
   * @brief Function for setting a start point of the timer. End time is taken
   * in the destructor.
   *
   */
  auto start() -> void {
    start_time = std::chrono::high_resolution_clock::now();
  }

private:
  std::chrono::high_resolution_clock::time_point start_time;
  std::size_t m_iterations{};
};
/**
 * @brief Returns a random matrix given by prng. This implements an `std::array`
 * base and aligns the matrix in memory.
 *
 * @tparam T Type of the matrix; constrained to types supported by prng.
 * @tparam Row Specifies the size of the row.
 * @tparam Col Specifies the size of col.
 * @param prng function wrapper for prng, defaults to `std::mt19937`
 * @return `Matrix<T, Row, Col>` random matrix described by prng.
 */
template <typename T, std::size_t Row, std::size_t Col,
          typename = std::enable_if_t<std::is_arithmetic_v<T>>>
auto make_matrix(std::reference_wrapper<std::mt19937> prng)
    -> Matrix<T, Row, Col> {

  std::array<T, Row * Col> result;
  std::generate_n(std::back_inserter(result), Row * Col, prng);

  // std::generate_n(result.data(), Row * Col, prng);
  return Matrix<T, Row, Col>{result};
}
/**
 * @brief Returns a random matrix given by prng. This implements `std::vector`
 * base to hold for larger size matrices that goes beyond the stack limit of
 * `std::array`.
 *
 * @tparam T Type of the matrix; constrained to types supported by prng.
 * @tparam Row Specifies the size of the row.
 * @tparam Col Specifies the size of col.
 * @param prng function wrapper for prng, defaults to `std::mt19937`
 * @return `Matrix<T, Row, Col>` random matrix described by prng.
 */
template <typename T, std::size_t Row, std::size_t Col,
          typename = std::enable_if_t<std::is_arithmetic_v<T>>>
auto make_vmatrix(std::reference_wrapper<std::mt19937> prng)
    -> Matrix<T, Row, Col> {

  std::vector<T> result;
  result.reserve(Row * Col);

  std::generate_n(std::back_inserter(result), Row * Col, prng);

  // std::generate_n(result.data(), Row * Col, prng);
  return Matrix<T, Row, Col>{result};
}
/**
 * @brief Operator overload to display the matrix in `std::cout`.
 *
 * @tparam T Type of the matrix.
 * @tparam Row Specifies the size of the row.
 * @tparam Col Specifies the size of the col.
 * @param os `std::ostream` that records the buffer to be printed.
 * @param matrix matrix to be registered in the output buffer.
 * @return `std::ostream&` reference output buffer
 */
template <typename T, std::size_t Row, std::size_t Col>
auto operator<<(std::ostream &os,
                const lm::Matrix<T, Row, Col> &matrix) -> std::ostream & {
  static_assert(std::is_arithmetic_v<T>,
                "template parameter must be of type arithmetic");

  // if (matrix.empty()) {
  //   os << "[]" << std::endl;
  //   return os;
  // }

  std::size_t max_width = 0;
  for (std::size_t i = 0; i < Row; i++) {
    for (std::size_t j = 0; j < Col; j++) {
      std::size_t width = std::to_string(matrix(i, j)).size();
      if (width > max_width) {
        max_width = width;
      }
    }
  }

  os << "[";
  for (std::size_t i = 0; i < Row; ++i) {
    if (i != 0) {
      os << " ";
    }
    os << "[";
    for (std::size_t j = 0; j < Col; ++j) {
      os << std::setw(max_width) << matrix(i, j);
      if (j != Col - 1) {
        os << ", ";
      }
    }
    os << "]";
    if (i != Row - 1) {
      os << '\n';
    }
  }
  return os << "]\n";
}
/**
 * @brief Operator overload to display the vector of type `std::array`.
 *
 * @tparam T Type of the vector
 * @tparam Row Specifies the size of the row.
 * @param os `std::ostream` that records the buffer to be printed.
 * @param v vector to be registered in the output buffer
 * @return `std::ostream&` reference to the output buffer
 */
template <typename T, std::size_t Row>
auto operator<<(std::ostream &os,
                const std::array<T, Row> &v) -> std::ostream & {
  os << "[";
  for (const auto i : v) {
    os << i << " ";
  }
  return os << "]\n";
};

} // namespace lm

#endif // __UTILS_H__