#ifndef __LAZYOPS_H__
#define __LAZYOPS_H__

#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"

#include <cmath>
#include <functional>
#include <type_traits>

namespace lm {

template <typename T, std::size_t Row, std::size_t Col>
constexpr auto operator==(const Matrix<T, Row, Col> &lhs,
                          const Matrix<T, Row, Col> &rhs) -> bool {
  return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template <typename T, std::size_t Row, std::size_t Col>
constexpr auto operator!=(const Matrix<T, Row, Col> &lhs,
                          const Matrix<T, Row, Col> &rhs) -> bool {
  return !(lhs == rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator+(const Lhs &lhs, const Rhs &rhs) {
  if constexpr (std::is_arithmetic_v<Rhs>)
    return BinaryExpr<std::plus<>, Lhs, Scalar<Rhs>>(lhs, Scalar<Rhs>(rhs));
  if constexpr (std::is_arithmetic_v<Lhs>)
    return BinaryExpr<std::plus<>, Scalar<Lhs>, Rhs>(Scalar<Lhs>(lhs), rhs);
  return BinaryExpr<std::plus<>, Lhs, Rhs>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator-(const Lhs &lhs,
                         const Rhs &rhs) -> BinaryExpr<std::minus<>, Lhs, Rhs> {
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
// matmul unary: matmul(Expr(A), B) | matmul(A, Expr(B))
// matmul binary: matmul(Expr(A), Expr(B))
template <typename Lhs, typename Rhs>
constexpr auto matmul(const Lhs &lhs, const Rhs &rhs) -> MatMulExpr<Lhs, Rhs> {
  return MatMulExpr<Lhs, Rhs>(lhs, rhs);
}

struct Mod {
  template <typename Lhs, typename Rhs> auto operator()(Lhs l, Rhs r) const {
    return l % r;
  }
};

template <typename Lhs, typename Rhs>
constexpr auto operator%(const Lhs &lhs,
                         const Rhs &rhs) -> BinaryExpr<Mod, Lhs, Rhs> {
  return BinaryExpr<Mod, Lhs, Rhs>(lhs, rhs);
}

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

struct Log10Op {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log10(t);
  }
};

template <typename Expr>
auto log10(const Expr &expr) -> UnaryExpr<Log10Op, Expr> {
  return UnaryExpr<Log10Op, Expr>(expr);
}

struct Log2Op {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log2(t);
  }
};

template <typename Expr>
auto log2(const Expr &expr) -> UnaryExpr<Log2Op, Expr> {
  return UnaryExpr<Log2Op, Expr>(expr);
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

struct Exp2Op {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::exp2(t);
  }
};

template <typename Expr>
auto exp2(const Expr &expr) -> UnaryExpr<Exp2Op, Expr> {
  return UnaryExpr<Exp2Op, Expr>(expr);
}

struct SqrtOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::sqrt(t);
  }
};

template <typename Expr>
auto sqrt(const Expr &expr) -> UnaryExpr<SqrtOp, Expr> {
  return UnaryExpr<SqrtOp, Expr>(expr);
}

struct CbrtOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::cbrt(t);
  }
};

template <typename Expr>
auto cbrt(const Expr &expr) -> UnaryExpr<CbrtOp, Expr> {
  return UnaryExpr<CbrtOp, Expr>(expr);
}

struct SinOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::sin(t);
  }
};

template <typename Expr> auto sin(const Expr &expr) -> UnaryExpr<SinOp, Expr> {
  return UnaryExpr<SinOp, Expr>(expr);
}

struct CosOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::cos(t);
  }
};

template <typename Expr> auto cos(const Expr &expr) -> UnaryExpr<CosOp, Expr> {
  return UnaryExpr<CosOp, Expr>(expr);
}

struct TanOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::tan(t);
  }
};

template <typename Expr> auto tan(const Expr &expr) -> UnaryExpr<TanOp, Expr> {
  return UnaryExpr<TanOp, Expr>(expr);
}

struct ASinOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::asin(t);
  }
};

template <typename Expr>
auto asin(const Expr &expr) -> UnaryExpr<ASinOp, Expr> {
  return UnaryExpr<ASinOp, Expr>(expr);
}

struct ACosOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::acos(t);
  }
};

template <typename Expr>
auto acos(const Expr &expr) -> UnaryExpr<ACosOp, Expr> {
  return UnaryExpr<ACosOp, Expr>(expr);
}

struct ATanOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::atan(t);
  }
};

template <typename Expr>
auto atan(const Expr &expr) -> UnaryExpr<ATanOp, Expr> {
  return UnaryExpr<ATanOp, Expr>(expr);
}

struct SinhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::sinh(t);
  }
};

template <typename Expr>
auto sinh(const Expr &expr) -> UnaryExpr<SinhOp, Expr> {
  return UnaryExpr<SinhOp, Expr>(expr);
}

struct CoshOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::cosh(t);
  }
};

template <typename Expr>
auto cosh(const Expr &expr) -> UnaryExpr<CoshOp, Expr> {
  return UnaryExpr<CoshOp, Expr>(expr);
}

struct TanhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::tanh(t);
  }
};

template <typename Expr>
auto tanh(const Expr &expr) -> UnaryExpr<TanhOp, Expr> {
  return UnaryExpr<TanhOp, Expr>(expr);
}

struct ASinhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::asinh(t);
  }
};

template <typename Expr>
auto asinh(const Expr &expr) -> UnaryExpr<ASinhOp, Expr> {
  return UnaryExpr<ASinhOp, Expr>(expr);
}

struct ACoshOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::acosh(t);
  }
};

template <typename Expr>
auto acosh(const Expr &expr) -> UnaryExpr<ACoshOp, Expr> {
  return UnaryExpr<ACoshOp, Expr>(expr);
}

struct ATanhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::atanh(t);
  }
};

template <typename Expr>
auto atanh(const Expr &expr) -> UnaryExpr<ATanhOp, Expr> {
  return UnaryExpr<ATanhOp, Expr>(expr);
}

struct ToDeg {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return t * 180. / M_PI;
  }
};

template <typename Expr>
auto to_deg(const Expr &expr) -> UnaryExpr<ToDeg, Expr> {
  return UnaryExpr<ToDeg, Expr>(expr);
}

struct ToRad {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return t * M_PI / 180.;
  }
};

template <typename Expr>
auto to_rad(const Expr &expr) -> UnaryExpr<ToRad, Expr> {
  return UnaryExpr<ToRad, Expr>(expr);
}

struct ErfOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::erf(t);
  }
};

template <typename Expr> auto erf(const Expr &expr) -> UnaryExpr<ErfOp, Expr> {
  return UnaryExpr<ErfOp, Expr>(expr);
}

struct ErfcOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::erfc(t);
  }
};

template <typename Expr>
auto erfc(const Expr &expr) -> UnaryExpr<ErfcOp, Expr> {
  return UnaryExpr<ErfcOp, Expr>(expr);
}

struct TGammaOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::tgamma(t);
  }
};

template <typename Expr>
auto tgamma(const Expr &expr) -> UnaryExpr<TGammaOp, Expr> {
  return UnaryExpr<TGammaOp, Expr>(expr);
}

struct LGammaOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::lgamma(t);
  }
};

template <typename Expr>
auto lgamma(const Expr &expr) -> UnaryExpr<LGammaOp, Expr> {
  return UnaryExpr<LGammaOp, Expr>(expr);
}

struct CeilOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::ceil(t);
  }
};

template <typename Expr>
auto ceil(const Expr &expr) -> UnaryExpr<CeilOp, Expr> {
  return UnaryExpr<CeilOp, Expr>(expr);
}

struct FloorOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::floor(t);
  }
};

template <typename Expr>
auto floor(const Expr &expr) -> UnaryExpr<FloorOp, Expr> {
  return UnaryExpr<FloorOp, Expr>(expr);
}
}; // namespace lm

#endif // __LAZYOPS_H__