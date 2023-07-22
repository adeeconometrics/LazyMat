#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <random>

using namespace lm;
using std::cout;

auto main() -> int {
  std::mt19937 rng(10);
  const auto A = make_matrix<int>(4, 4, std::ref(rng));

  cout << A;
  return 0;
}