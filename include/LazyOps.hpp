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
constexpr auto operator+(const Lhs &lhs, const Rhs &rhs)
    -> MatExpr<BinaryExpr<std::plus<>, Lhs, Rhs>> {
  return MatExpr<BinaryExpr<std::plus<>, Lhs, Rhs>>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator-(const Lhs &lhs, const Rhs &rhs)
    -> MatExpr<BinaryExpr<std::minus<>, Lhs, Rhs>> {
  return MatExpr<BinaryExpr<std::minus<>, Lhs, Rhs>>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator*(const Lhs &lhs, const Rhs &rhs)
    -> MatExpr<BinaryExpr<std::multiplies<>, Lhs, Rhs>> {
  return MatExpr<BinaryExpr<std::multiplies<>, Lhs, Rhs>>(lhs, rhs);
}

template <typename Lhs, typename Rhs>
constexpr auto operator/(const Lhs &lhs, const Rhs &rhs)
    -> MatExpr<BinaryExpr<std::divides<>, Lhs, Rhs>> {
  return MatExpr<BinaryExpr<std::divides<>, Lhs, Rhs>>(lhs, rhs);
}
// matmul unary: matmul(Expr(A), B) | matmul(A, Expr(B))
// matmul binary: matmul(Expr(A), Expr(B))
template <typename Lhs, typename Rhs>
constexpr auto matmul(const Lhs &lhs,
                      const Rhs &rhs) -> MatExpr<MatMulExpr<Lhs, Rhs>> {
  return MatExpr<MatMulExpr<Lhs, Rhs>>(lhs, rhs);
}

struct ModOp {
  template <typename Lhs, typename Rhs> auto operator()(Lhs l, Rhs r) const {
    return l % r;
  }
};

template <typename Lhs, typename Rhs>
constexpr auto operator%(const Lhs &lhs, const Rhs &rhs)
    -> MatExpr<BinaryExpr<ModOp, Lhs, Rhs>> {
  return MatExpr<BinaryExpr<ModOp, Lhs, Rhs>>(lhs, rhs);
}

struct PowOp {
  template <typename Lhs, typename Rhs> auto operator()(Lhs l, Rhs r) const {
    return std::pow(l, r);
  }
};

template <typename Lhs, typename Rhs,
          typename = typename std::enable_if_t<std::is_arithmetic_v<Rhs>>>
constexpr auto pow(const Lhs &lhs,
                   const Rhs &rhs) -> MatExpr<BinaryExpr<PowOp, Lhs, Rhs>> {
  return MatExpr<BinaryExpr<PowOp, Lhs, Rhs>>(lhs, rhs);
}

template <typename Expr>
constexpr auto
operator-(const Expr &expr) -> MatExpr<UnaryExpr<std::negate<>, Expr>> {
  return MatExpr<UnaryExpr<std::negate<>, Expr>>(expr);
}

struct LogOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log(t);
  }
};

template <typename Expr>
auto log(const Expr &expr) -> MatExpr<UnaryExpr<LogOp, Expr>> {
  return MatExpr<UnaryExpr<LogOp, Expr>>(expr);
}

struct Log10Op {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log10(t);
  }
};

template <typename Expr>
auto log10(const Expr &expr) -> MatExpr<UnaryExpr<Log10Op, Expr>> {
  return MatExpr<UnaryExpr<Log10Op, Expr>>(expr);
}

struct Log2Op {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::log2(t);
  }
};

template <typename Expr>
auto log2(const Expr &expr) -> MatExpr<UnaryExpr<Log2Op, Expr>> {
  return MatExpr<UnaryExpr<Log2Op, Expr>>(expr);
}

struct ExpOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::exp(t);
  }
};

template <typename Expr>
auto exp(const Expr &expr) -> MatExpr<UnaryExpr<ExpOp, Expr>> {
  return MatExpr<UnaryExpr<ExpOp, Expr>>(expr);
}

struct Exp2Op {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::exp2(t);
  }
};

template <typename Expr>
auto exp2(const Expr &expr) -> MatExpr<UnaryExpr<Exp2Op, Expr>> {
  return MatExpr<UnaryExpr<Exp2Op, Expr>>(expr);
}

struct SqrtOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::sqrt(t);
  }
};

template <typename Expr>
auto sqrt(const Expr &expr) -> MatExpr<UnaryExpr<SqrtOp, Expr>> {
  return MatExpr<UnaryExpr<SqrtOp, Expr>>(expr);
}

struct CbrtOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::cbrt(t);
  }
};

template <typename Expr>
auto cbrt(const Expr &expr) -> MatExpr<UnaryExpr<CbrtOp, Expr>> {
  return MatExpr<UnaryExpr<CbrtOp, Expr>>(expr);
}

struct SinOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::sin(t);
  }
};

template <typename Expr>
auto sin(const Expr &expr) -> MatExpr<UnaryExpr<SinOp, Expr>> {
  return MatExpr<UnaryExpr<SinOp, Expr>>(expr);
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

template <typename Expr>
auto tan(const Expr &expr) -> MatExpr<UnaryExpr<TanOp, Expr>> {
  return MatExpr<UnaryExpr<TanOp, Expr>>(expr);
}

struct ASinOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::asin(t);
  }
};

template <typename Expr>
auto asin(const Expr &expr) -> MatExpr<UnaryExpr<ASinOp, Expr>> {
  return MatExpr<UnaryExpr<ASinOp, Expr>>(expr);
}

struct ACosOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::acos(t);
  }
};

template <typename Expr>
auto acos(const Expr &expr) -> MatExpr<UnaryExpr<ACosOp, Expr>> {
  return MatExpr<UnaryExpr<ACosOp, Expr>>(expr);
}

struct ATanOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::atan(t);
  }
};

template <typename Expr>
auto atan(const Expr &expr) -> MatExpr<UnaryExpr<ATanOp, Expr>> {
  return MatExpr<UnaryExpr<ATanOp, Expr>>(expr);
}

struct SinhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::sinh(t);
  }
};

template <typename Expr>
auto sinh(const Expr &expr) -> MatExpr<UnaryExpr<SinhOp, Expr>> {
  return MatExpr<UnaryExpr<SinhOp, Expr>>(expr);
}

struct CoshOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::cosh(t);
  }
};

template <typename Expr>
auto cosh(const Expr &expr) -> MatExpr<UnaryExpr<CoshOp, Expr>> {
  return MatExpr<UnaryExpr<CoshOp, Expr>>(expr);
}

struct TanhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::tanh(t);
  }
};

template <typename Expr>
auto tanh(const Expr &expr) -> MatExpr<UnaryExpr<TanhOp, Expr>> {
  return MatExpr<UnaryExpr<TanhOp, Expr>>(expr);
}

struct ASinhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::asinh(t);
  }
};

template <typename Expr>
auto asinh(const Expr &expr) -> MatExpr<UnaryExpr<ASinhOp, Expr>> {
  return MatExpr<UnaryExpr<ASinhOp, Expr>>(expr);
}

struct ACoshOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::acosh(t);
  }
};

template <typename Expr>
auto acosh(const Expr &expr) -> MatExpr<UnaryExpr<ACoshOp, Expr>> {
  return MatExpr<UnaryExpr<ACoshOp, Expr>>(expr);
}

struct ATanhOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::atanh(t);
  }
};

template <typename Expr>
auto atanh(const Expr &expr) -> MatExpr<UnaryExpr<ATanhOp, Expr>> {
  return MatExpr<UnaryExpr<ATanhOp, Expr>>(expr);
}

struct ToDeg {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return t * 180. / M_PI;
  }
};

template <typename Expr>
auto to_deg(const Expr &expr) -> MatExpr<UnaryExpr<ToDeg, Expr>> {
  return MatExpr<UnaryExpr<ToDeg, Expr>>(expr);
}

struct ToRad {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return t * M_PI / 180.;
  }
};

template <typename Expr>
auto to_rad(const Expr &expr) -> MatExpr<UnaryExpr<ToRad, Expr>> {
  return MatExpr<UnaryExpr<ToRad, Expr>>(expr);
}

struct ErfOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::erf(t);
  }
};

template <typename Expr>
auto erf(const Expr &expr) -> MatExpr<UnaryExpr<ErfOp, Expr>> {
  return MatExpr<UnaryExpr<ErfOp, Expr>>(expr);
}

struct ErfcOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::erfc(t);
  }
};

template <typename Expr>
auto erfc(const Expr &expr) -> MatExpr<UnaryExpr<ErfcOp, Expr>> {
  return MatExpr<UnaryExpr<ErfcOp, Expr>>(expr);
}

struct TGammaOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::tgamma(t);
  }
};

template <typename Expr>
auto tgamma(const Expr &expr) -> MatExpr<UnaryExpr<TGammaOp, Expr>> {
  return MatExpr<UnaryExpr<TGammaOp, Expr>>(expr);
}

struct LGammaOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::lgamma(t);
  }
};

template <typename Expr>
auto lgamma(const Expr &expr) -> MatExpr<UnaryExpr<LGammaOp, Expr>> {
  return MatExpr<UnaryExpr<LGammaOp, Expr>>(expr);
}

struct CeilOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::ceil(t);
  }
};

template <typename Expr>
auto ceil(const Expr &expr) -> MatExpr<UnaryExpr<CeilOp, Expr>> {
  return MatExpr<UnaryExpr<CeilOp, Expr>>(expr);
}

struct FloorOp {
  template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
  auto operator()(T t) const {
    return std::floor(t);
  }
};

template <typename Expr>
auto floor(const Expr &expr) -> MatExpr<UnaryExpr<FloorOp, Expr>> {
  return MatExpr<UnaryExpr<FloorOp, Expr>>(expr);
}
}; // namespace lm

#endif // __LAZYOPS_H__