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

template <typename Op, typename Expr> class UnaryExpr {
public:
  UnaryExpr(const Expr &expr) : expr(expr) {}

  auto operator()(std::size_t i, std::size_t j) const { return op(expr(i, j)); }

private:
  Expr expr;
  Op op;
};

} // namespace lm

#endif // __LAZYEXPR_H__