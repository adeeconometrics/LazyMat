#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;

auto main() -> int {
  const Matrix<float> A{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};

  Matrix<float> B(3, 3);
  B = log(A);

  std::cout << A << "----------------\n\n";

  std::cout << B << "\n\n";
  B = log10(A);
  std::cout << B << "\n\n";
  B = log2(A);
  std::cout << B << "\n\n";

  return 0;
}