#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {

  std::mt19937 rng_a(67);
  std::mt19937 rng_b(65);

  Matrix<int, 256, 256> A{make_matrix<int, 256, 256>(std::ref(rng_a))};
  Matrix<int, 256, 256> B{make_matrix<int, 256, 256>(std::ref(rng_b))};

  Matrix<int, 256, 256> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
  // B = log(A);

  return 0;
}