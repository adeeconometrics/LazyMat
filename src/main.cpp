#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {
  std::mt19937 rng(11);
  const auto A = make_matrix<int>(4, 4, std::ref(rng));
  Matrix<float> B(4, 4);
  B = log(A) * A + A;

  std::cout << A << "----------------\n\n";

  std::cout << B;
  return 0;
}