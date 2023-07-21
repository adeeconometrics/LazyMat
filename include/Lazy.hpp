#ifndef __LAZY_H__
#define __LAZY_H__

#include <functional>
#include <vector>

// todo
// remove OpType
// add unary ops
// add mat size checking -- runtime
// specialized type impl

// revise opnode as class that maintains a reference of a matrix type
namespace lm {

using Mat = std::vector<std::vector<float>>;

enum class OpType { Addition, Multiplication };

struct OpNode {
  OpType type;
  std::function<float(float, float)> op;
  std::vector<Mat> matrices;
  std::vector<OpNode> children; // make this shared (instance var)
};

auto operator+(const Mat &A, const Mat &B) -> OpNode {
  return {OpType::Addition, std::plus<float>(), {A, B}};
}

auto operator*(const Mat &A, const Mat &B) -> OpNode {
  return {OpType::Multiplication, std::multiplies<float>(), {A, B}};
}

auto operator+(const OpNode &lhs, const OpNode &rhs) -> OpNode {
  OpNode result;
  result.type = OpType::Addition;
  result.op = std::plus<float>();
  result.children = {rhs, lhs};
  return result;
}

auto operator*(const OpNode &lhs, const OpNode &rhs) -> OpNode {
  OpNode result;
  result.type = OpType::Addition;
  result.op = std::multiplies<float>();
  result.children = {rhs, lhs};
  return result;
}

auto apply(const OpNode &opnode) -> Mat {
  if (opnode.matrices.empty()) {
    // Evaluate the children recursively
    if (opnode.children.empty()) {
      return {};
    }
    Mat result = apply(opnode.children[0]);
    for (size_t i = 1; i < opnode.children.size(); ++i) {
      const Mat &matrix = apply(opnode.children[i]);
      for (size_t j = 0; j < result.size(); ++j) {
        for (size_t k = 0; k < result[j].size(); ++k) {
          result[j][k] = opnode.op(result[j][k], matrix[j][k]);
        }
      }
    }
    return result;
  } else {
    // Perform the operation on the input matrices
    if (opnode.matrices.size() < 2) {
      return opnode.matrices[0];
    }
    Mat result = opnode.matrices[0];
    for (size_t i = 1; i < opnode.matrices.size(); ++i) {
      const Mat &matrix = opnode.matrices[i];
      for (size_t j = 0; j < result.size(); ++j) {
        for (size_t k = 0; k < result[j].size(); ++k) {
          result[j][k] = opnode.op(result[j][k], matrix[j][k]);
        }
      }
    }
    return result;
  }
}
} // namespace lm

#endif // __LAZY_H__