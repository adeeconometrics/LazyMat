#include "../include/Eager.hpp"
#include "../include/Values.hpp"
#include <iostream>

using namespace lm;
using std::cout;

auto main() -> int {

  // EMat A = {{1.0f, 2.0f}, {3.0f, 4.0f}};
  // Mat B = {{5.0f, 6.0f}, {7.0f, 8.0f}};
  // Mat C = {{9.0f, 10.0f}, {11.0f, 12.0f}};
  // Mat D = {{13.0f, 14.0f}, {15.0f, 16.0f}};

  // Build the computational graph
  // OpNode addNode = A + B;
  // OpNode mulNode = C * D;
  auto sub1 = A * A;
  auto sub2 = A + A;
  auto rootNode = sub1 * sub2;
  // Apply the operation
  // Mat result = apply(rootNode);

  cout << "dims: " << A.size() << "x" << A[0].size() << " done!";

  return 0;
}