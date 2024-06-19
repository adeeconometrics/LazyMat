#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"
#include "../include/Utils.hpp"

#include <random>

using namespace lm;

auto main(int argc, char **argv) -> int {

  std::mt19937 rng_a(67);
  std::mt19937 rng_b(65);

  // get the matrix dimensions from command line

  constexpr int M = 4096 * 2;
  constexpr int N = 4096 * 2;
  constexpr int K = 4096 * 2;

  Matrix<float, M, N> A{make_vmatrix<float, M, N>(std::ref(rng_a))};
  Matrix<float, N, K> B{make_vmatrix<float, N, K>(std::ref(rng_b))};

  // Matrix<float, K, N> C;
  {
    const std::size_t iterations = 3;
    Timer t{iterations};
    t.start();
    for (std::size_t i = 0; i < iterations; i++) {
      auto C = 2 + matmul(A, B) + A * B * matmul(sin(A), cos(A) + B) + 3.;
    }
  }

  // B = log(A);

  return 0;
}