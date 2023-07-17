#include "../include/Mat.hpp"
#include <iostream>

using namespace lm;

auto main() -> int {
  Mat A = {{1.0f, 2.0f}, {3.0f, 4.0f}};
  Mat B = {{5.0f, 6.0f}, {7.0f, 8.0f}};
  Mat C = {{9.0f, 10.0f}, {11.0f, 12.0f}};
  Mat D = {{13.0f, 14.0f}, {15.0f, 16.0f}};

  // Build the computational graph
  OpNode addNode = A + B;
  OpNode mulNode = C * D;
  OpNode rootNode;
  rootNode.type = OpType::Addition;
  rootNode.op = [](float a, float b) { return a + b; };
  rootNode.children = {addNode, mulNode};

  // Apply the operation
  Mat result = apply(rootNode);

  std::cout << "Result of A*B+C*D:" << std::endl;
  for (const auto &row : result) {
    for (const auto &element : row) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}