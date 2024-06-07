#ifndef __LAZYEXPR_H__
#define __LAZYEXPR_H__

#include <type_traits>
namespace lm {
template <typename T,
          typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
class Scalar {
public:
  Scalar(const T &value) : value(value) {}

  T operator()(std::size_t i, std::size_t j) const noexcept { return value; }

private:
  T value;
};
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

  // template <typename T = Lhs, typename U = Rhs,
  //           typename = typename std::enable_if_t<!std::disjunction_v<
  //               std::is_arithmetic<T>, std::is_arithmetic<U>>>>
  auto operator()(std::size_t i, std::size_t j) const noexcept {
    if constexpr (std::is_arithmetic_v<Rhs>) {
      return op(lhs(i, j), rhs);
    }

    if constexpr (std::is_arithmetic_v<Lhs>) {
      return op(lhs, rhs(i, j));
    }

    return op(lhs(i, j), rhs(i, j));
  }

  // template <typename T = Rhs, std::enable_if_t<std::is_arithmetic_v<T>>>
  // auto operator()(std::size_t i, std::size_t j) const noexcept {
  //   return op(lhs(i, j), rhs);
  // }

  // // template <typename T = Lhs, std::enable_if_t<std::is_arithmetic_v<T>>>
  // // auto operator()(std::size_t i, std::size_t j) const noexcept {
  // //   return op(lhs, rhs(i, j));
  // // }

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

  auto rows() const { return expr.rows(); }
  auto cols() const { return expr.cols(); }

private:
  Expr expr;
  Op op;
};

// template <typename Op, typename Lhs, typename Rhs>
// auto make_expr(const Lhs &lhs, const Rhs &rhs) {
//   if constexpr (std::is_arithmetic_v<Rhs>) {
//     return BinaryExpr<Op, Lhs, Scalar<Rhs>>(lhs, Scalar<Rhs>(rhs));
//   }
//   if constexpr (std::is_arithmetic_v<Lhs>) {
//     return BinaryExpr<Op, Scalar<Lhs>, Rhs>(Scalar<Lhs>(lhs), rhs);
//   }

//   return BinaryExpr<Op, Lhs, Rhs>(lhs, rhs);
// }
/**
 * @brief Template functor for matrix multiplication expressions. Contains an
 * operator() for evaluating the expression lazily. Works with `matmul(Expr,
 * Expr)` types to represent MatMulExpr<Ops,Ops> computation *
 * @tparam Lhs Left hand side of the expr.
 * @tparam Rhs Right hand side of the expr.
 */
template <typename Lhs, typename Rhs> class MatMulExpr {
public:
  MatMulExpr(const Lhs &lhs, const Rhs &rhs) : m_lhs(lhs), m_rhs(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const {
    auto result = m_lhs(i, 0) * m_rhs(0, j);
#ifdef __clang__
#pragma clang loop vectorize(enable)
#endif
    for (std::size_t k = 1; k < m_lhs.cols(); ++k) {
      result += m_lhs(i, k) * m_rhs(k, j);
    }
    return result;
  }

  std::size_t rows() const { return m_lhs.rows(); }
  std::size_t cols() const { return m_rhs.cols(); }

private:
  Lhs m_lhs;
  Rhs m_rhs;
};

} // namespace lm

#endif // __LAZYEXPR_H__