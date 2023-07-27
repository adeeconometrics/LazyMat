#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {
  const Matrix<float, 3, 3> A{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};

  Matrix<float, 3, 3> B;
  // B = log(A);

  return 0;
}