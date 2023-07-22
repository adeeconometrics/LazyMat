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

template <typename Lhs, typename Rhs>
constexpr auto operator+(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::plus<>, Lhs, Rhs> {
  return BinaryExpr<std::plus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator-(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::minus<>, Lhs, Rhs> {
  return BinaryExpr<std::minus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator*(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::multiplies<>, Lhs, Rhs> {
  return BinaryExpr<std::multiplies<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator/(const Lhs &lhs, const Rhs &rhs)
    -> BinaryExpr<std::divides<>, Lhs, Rhs> {
  return BinaryExpr<std::divides<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Op, typename Expr> class UnaryExpr {
public:
  UnaryExpr(const Expr &expr) : expr(expr) {}

  auto operator()(std::size_t i, std::size_t j) const { return op(expr(i, j)); }

private:
  Expr expr;
  Op op;
};

template <typename Expr>
constexpr auto operator-(const Expr &expr) -> UnaryExpr<std::negate<>, Expr> {
  return UnaryExpr<std::negate<>, Expr>(expr);
}

struct LogOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log(t);
  }
};

template <typename Expr> auto log(const Expr &expr) -> UnaryExpr<LogOp, Expr> {
  return UnaryExpr<LogOp, Expr>(expr);
}

struct ExpOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::exp(t);
  }
};

template <typename Expr> auto exp(const Expr &expr) -> UnaryExpr<ExpOp, Expr> {
  return UnaryExpr<ExpOp, Expr>(expr);
}

} // namespace lm

#endif // __LAZYEXPR_H__