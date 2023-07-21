// contains impl of lazy matrix

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

using Mat = std::vector<std::vector<float>>;

struct OpNode {
  explicit OpNode(
      const std::function<float(float, float)> &t_op,
      const std::vector<std::reference_wrapper<const Mat>> &t_matrices)
      : op(t_op), matrices(t_matrices) {}

  explicit OpNode(
      const std::function<float(float, float)> &t_op,
      const std::vector<std::reference_wrapper<const OpNode>> &t_children)
      : op(t_op), children(t_children) {
    // std::cout << "children overload constructor is properly called.\n";
  }

  explicit OpNode(
      const std::function<float(float, float)> &t_op,
      const std::vector<std::reference_wrapper<const Mat>> &t_matrices,
      const std::vector<std::reference_wrapper<const OpNode>> &t_children)
      : op(t_op), matrices(t_matrices), children(t_children) {}

  std::function<float(float, float)> op;
  std::vector<std::reference_wrapper<const Mat>> matrices;
  std::vector<std::reference_wrapper<const OpNode>> children;
  // make this shared (instance var)
};

auto operator+(const Mat &A, const Mat &B) -> OpNode {
  return OpNode(std::plus<float>(), {std::cref(A), std::cref(B)});
}

auto operator*(const Mat &A, const Mat &B) -> OpNode {
  return OpNode(std::multiplies<float>(), {A, B});
}

auto operator+(const OpNode &lhs, const OpNode &rhs) -> OpNode {
  //   std::cout
  //       << "OpNode with children is called, children overload is expected\n";
  return OpNode(std::plus<float>(), {std::cref(lhs), std::cref(rhs)});
}

auto operator*(const OpNode &lhs, const OpNode &rhs) -> OpNode {
  //   std::cout
  //       << "OpNode with children is called, children overload is expected\n";
  return OpNode(std::multiplies<float>(), {std::cref(lhs), std::cref(rhs)});
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

auto make_matrix(std::size_t row, std::size_t col,
                 std::reference_wrapper<std::mt19937> rng) -> Mat {
  Mat result;
  result.reserve(row);
  for (std::size_t i = 0; i < row; i++) {
    std::vector<float> row;
    row.reserve(col);
    std::generate_n(std::back_inserter(row), col, rng);
    result.emplace_back(row);
  }

  return result;
}

auto main() -> int {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  const auto A = make_matrix(2048, 2048, rng_a);
  const auto B = make_matrix(2048, 2048, rng_b);

  auto sub1 = A * B;
  auto sub2 = A + B;
  auto rootNode = sub1 * sub2;

  std::cout << "A: " << A.size() << "x" << A[0].size() << " dims\n";
  std::cout << "B: " << B.size() << "x" << B[0].size() << " dims\n";
}
