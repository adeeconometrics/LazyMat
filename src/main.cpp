#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"
#include "../include/Utils.hpp"

#include <random>

using namespace lm;

auto main() -> int {

  std::mt19937 rng_a(67);
  std::mt19937 rng_b(65);

  constexpr int M = 3;
  constexpr int N = 3;
  constexpr int K = 3;

  Matrix<float, M, N> A{make_vmatrix<float, M, N>(std::ref(rng_a))};
  Matrix<float, M, K> B{make_vmatrix<float, M, K>(std::ref(rng_b))};

  Matrix<float, K, N> C;
  {
    const std::size_t iterations = 3;
    Timer t{iterations};
    t.start();
    for (std::size_t i = 0; i < iterations; i++) {
      C = 2 + matmul(A, B) + A * B * matmul(sin(A), cos(A) + B) + 3.;
    }
  }

  // B = log(A);

  return 0;
}