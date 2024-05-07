#ifndef __LAZYEXPR_H__
#define __LAZYEXPR_H__

#include "../include/LazyMatrix.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

// todo
// add mat size checking -- runtime
// specialized type impl

namespace lm {
/**
 * @brief Template functor for binary expressions. Contains an abstract
 * representation of binary ops and an API for recursively calling eval via
 * `operator()` overload.
 *
 * @tparam Op Operator type specified in `LazyOps.hpp`
 * @tparam Lhs Left hand side of the expr.
 * @tparam Rhs Righ hand side of the expr.
 */
template <typename Op, typename Lhs, typename Rhs> class BinaryExpr {
public:
  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const noexcept {
    return op(lhs(i, j), rhs(i, j));
  }

private:
  Lhs lhs;
  Rhs rhs;
  Op op;
};
/**
 * @brief Template functor for unary expressions. Contains an abstract
 * representation of unary ops and an API for recursively calling eval via
 * `operator()` overload.
 *
 * @tparam Op Operator type specified in `LazyOps.hpp`
 * @tparam Expr Unary expression
 */
template <typename Op, typename Expr> class UnaryExpr {
public:
  UnaryExpr(const Expr &expr) : expr(expr) {}

  auto operator()(std::size_t i, std::size_t j) const { return op(expr(i, j)); }

private:
  Expr expr;
  Op op;
};

template <typename Lhs, typename Rhs> class MatMulExpr {
public:
  constexpr MatMulExpr(const Lhs &lhs, const Rhs &rhs) : lhs_(lhs), rhs_(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const {
    auto result = lhs_(i, 0) * rhs_(0, j);
    for (std::size_t k = 1; k < lhs_.col(); ++k) {
      result += lhs_(i, k) * rhs_(k, j);
    }
    return result;
  }

  std::size_t rows() const { return lhs_.rows(); }
  std::size_t cols() const { return rhs_.cols(); }

private:
  const Lhs &lhs_;
  const Rhs &rhs_;
};
} // namespace lm

#endif // __LAZYEXPR_H__