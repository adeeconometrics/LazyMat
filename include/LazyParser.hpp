#ifndef __LAZYPARSER_H__
#define __LAZYPARSER_H__

#include "../include/LazyExpr.hpp"
#include "../include/LazyOps.hpp"

#include <string>

using lm::BinaryExpr;
using lm::UnaryExpr;

struct Sym final {

  std::string name;
};

// template <typename T> struct Parser {
//   static auto parse() -> std::string { return T::parse(); }
// };

// template <typename Op, typename Lhs, typename Rhs>
// struct Parser<BinaryExpr<Op, Lhs, Rhs>> {
//   static auto parse() -> std::string {
//     return Parser<Lhs>::parse() + " " + std::string(Op::name) + " " +
//            Parser<Lhs>::parse();
//   }
// };

// template <typename Op, typename Expr> struct Parser<UnaryExpr<Op, Expr>> {
//   static auto parse() -> std::string {
//     return std::string(Op::name) + "(" + Parser<Expr>::parse() + ")";
//   }
// };

// template <typename Lhs, typename Rhs> using Add = BinaryExpr<AddOp, Lhs,
// Rhs>;

// template <typename Arg> using Sin = UnaryExpr<SinOp, Arg>;

// implement parser

#endif // __LAZYPARSER_H__