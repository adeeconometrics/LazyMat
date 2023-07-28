#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {

  std::mt19937 rng(10);

  const Matrix<float, 3, 3> A{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};

  auto B = make_matrix<float, 3, 4>(std::ref(rng));
  std::cout << B;
  // B = log(A);

  return 0;
}