#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {

  std::mt19937 rng_a(67);
  std::mt19937 rng_b(65);

  Matrix<int, 128, 128> A{make_vmatrix<int, 128, 128>(std::ref(rng_a))};
  Matrix<int, 128, 128> B{make_vmatrix<int, 128, 128>(std::ref(rng_b))};

  Matrix<int, 128, 128> C;
  {
    Timer t;
    C = A * B * B + A * B + A * A * B;
  }
  // std::cout << C;
  // B = log(A);

  return 0;
}