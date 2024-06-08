#ifndef __LAZYPARSER_H__
#define __LAZYPARSER_H__

#include <string>
#include <type_traits>

template <typename T, std::size_t Row, std::size_t Col,
          typename = typename std::enable_if_t<std::is_arithmetic_v<T>>>
struct Symbol {

  Symbol() { m_counter++; }

  auto name() const noexcept -> std::string {
    return m_name + "_" + std::to_string(m_counter);
  }

private:
  static std::string m_name;
  static std::size_t m_counter;
};

template <typename T, std::size_t Rows, std::size_t Cols>
std::size_t Symbol<T, Rows, Cols>::m_counter = 0;

template <typename T, std::size_t Rows, std::size_t Cols>
std::string Symbol<T, Rows, Cols>::m_name = "x";

// implement parser

#endif // __LAZYPARSER_H__