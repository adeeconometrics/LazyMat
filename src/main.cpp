#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {

  std::mt19937 rng_a(67);
  std::mt19937 rng_b(65);

  constexpr int M = 1024;
  constexpr int N = 1024;
  constexpr int K = 1024;

  Matrix<int, M, N> A{make_vmatrix<int, M, N>(std::ref(rng_a))};
  Matrix<int, M, K> B{make_vmatrix<int, M, K>(std::ref(rng_b))};

  Matrix<int, K, N> C;
  {
    const std::size_t iterations = 3;
    Timer t{iterations};
    for (std::size_t i = 0; i < iterations; i++) {
      t.start();
      C = A * B + B / A * B * B - A;
    }
  }

  // B = log(A);

  return 0;
}