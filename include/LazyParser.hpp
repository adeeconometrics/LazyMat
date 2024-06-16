#ifndef __LAZYPARSER_H__
#define __LAZYPARSER_H__

#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"

#include <string>

using lm::BinaryExpr;
using lm::Matrix;
using lm::UnaryExpr;

struct Sym {
  Sym() {
    m_name = "X"; //+ std::to_string(inc());
  }
  Sym(std::string name) : m_name(std::move(name)) {}

private:
  std::string m_name;
  // static std::size_t m_counter;

private:
  // static auto inc() -> std::size_t { return m_counter++; }

public:
  auto get_name() const -> std::string { return m_name; }
  // static auto get_counter() -> std::size_t { return m_counter; }
};

// std::size_t Sym::m_counter = 0;

// Base template for parsing expressions
template <typename T> struct Parser {
  static std::string parse(const T &expr) { return T::parse(expr); }
};

// Parser specialization for binary expressions
template <typename Op, typename Lhs, typename Rhs>
struct Parser<BinaryExpr<Op, Lhs, Rhs>> {
  static std::string parse(const BinaryExpr<Op, Lhs, Rhs> &expr) {
    return Parser<Lhs>::parse(expr.lhs) + " " + Op::symbol.get_name() + " " +
           Parser<Rhs>::parse(expr.rhs);
  }
};

// Parser specialization for unary expressions
template <typename Op, typename Arg> struct Parser<UnaryExpr<Op, Arg>> {
  static std::string parse(const UnaryExpr<Op, Arg> &expr) {
    return Op::symbol.get_name() + "(" + Parser<Arg>::parse(expr.arg) + ")";
  }
};

// Parser specialization for Sym (operands)
template <> struct Parser<Sym> {
  static std::string parse(const Sym &symbol) { return symbol.get_name(); }
};

template <typename T, std::size_t Rows, std::size_t Cols>
struct Parser<Matrix<T, Rows, Cols>> {
  static std::string parse(const Matrix<T, Rows, Cols> &matrix) {
    return Matrix<T, Rows, Cols>::parse(matrix);
  }
};
// implement parser

#endif // __LAZYPARSER_H__