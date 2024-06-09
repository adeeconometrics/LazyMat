#ifndef __LAZYPARSER_H__
#define __LAZYPARSER_H__

#include "../include/LazyExpr.hpp"

#include <string>
#include <type_traits>

using lm::BinaryExpr;
using lm::UnaryExpr;

struct Sym final {

  std::string name;
};

template <typename T> struct Parser {
  static auto parse() -> std::string { return T::name(); }
};

template <typename Op, typename Lhs, typename Rhs>
struct Parser<BinaryExpr<Op, Lhs, Rhs>> {
  static auto parse() -> std::string {
    return Parser<Lhs>::parse() + " " + Op::name + " " + Parser<Lhs>::parse();
  }
};

template <typename Op, typename Expr> struct Parser<UnaryExpr<Op, Expr>> {
  static auto parse() -> std::string {
    return Op::name + "(" + Parser<Expr>::parse() + ")";
  }
};

// implement parser

#endif // __LAZYPARSER_H__