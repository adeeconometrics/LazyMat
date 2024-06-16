#ifndef __LAZYEXPR_H__
#define __LAZYEXPR_H__

#include <cassert>
#include <type_traits>
#include <utility>

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
template <typename Op, typename Lhs, typename Rhs, typename = void>
class BinaryExpr {

public:
  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const noexcept {
    return op(lhs(i, j), rhs(i, j));
  }

  auto rows() const -> std::pair<std::size_t, std::size_t> {
    return {lhs.rows(), rhs.rows()};
  }

  auto cols() const -> std::pair<std::size_t, std::size_t> {
    return {rhs.cols(), lhs.cols()};
  }

private:
  Lhs lhs;
  Rhs rhs;
  Op op;
};

template <typename Op, typename Lhs, typename Rhs>
class BinaryExpr<Op, Lhs, Rhs,
                 std::enable_if_t<std::is_arithmetic<Rhs>::value>> {
public:
  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const noexcept {
    return op(lhs(i, j), rhs);
  }

  auto rows() const -> std::pair<std::size_t, std::size_t> {
    return {lhs.rows(), 1};
  }

  auto cols() const -> std::pair<std::size_t, std::size_t> {
    return {lhs.cols(), 1};
  }

private:
  Lhs lhs;
  Rhs rhs;
  Op op;
};

template <typename Op, typename Lhs, typename Rhs>
class BinaryExpr<Op, Lhs, Rhs,
                 std::enable_if_t<std::is_arithmetic<Lhs>::value>> {
public:
  BinaryExpr(const Lhs &lhs, const Rhs &rhs) : lhs(lhs), rhs(rhs) {}

  auto operator()(std::size_t i, std::size_t j) const noexcept {
    return op(lhs, rhs(i, j));
  }

  auto rows() const -> std::pair<std::size_t, std::size_t> {
    return {1, rhs.rows()};
  }

  auto cols() const -> std::pair<std::size_t, std::size_t> {
    return {1, rhs.cols()};
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

  auto rows() const { return expr.rows(); }
  auto cols() const { return expr.cols(); }

private:
  Expr expr;
  Op op;
};

/**
 * @brief Template functor for matrix multiplication expressions. Contains an
 * operator() for evaluating the expression lazily. Works with `matmul(Expr,
 * Expr)` types to represent MatMulExpr<Ops,Ops> computation *
 * @tparam Lhs Left hand side of the expr.
 * @tparam Rhs Right hand side of the expr.
 */
template <typename Lhs, typename Rhs> class MatMulExpr {
public:
  MatMulExpr(const Lhs &lhs, const Rhs &rhs) : m_lhs(lhs), m_rhs(rhs) {
    assert(m_lhs.cols() == m_rhs.rows()); // dimensions mismatch
  }

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