#include "../include/utils.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

template <typename Type, std::size_t Row, std::size_t Col, typename = void>
class Matrix {
public:
  Matrix(){};

  auto operator()(std::size_t i, std::size_t j) -> Type & {
    return m_data.at(i * Col + j);
  }

  auto operator()(std::size_t i, std::size_t j) const -> const Type & {
    return m_data[i * Col + j];
  }

private:
  std::array<Type, Row * Col> m_data{};
};

// Define the paged Matrix specialization when Row*Col > 256*256
template <typename Type, std::size_t Row, std::size_t Col>
class Matrix<Type, Row, Col, std::enable_if_t<(Row * Col) >= (256 * 256)>> {
public:
  Matrix() {
    for (auto &page : m_pages)
      page = std::array<Type, page_size>{};
  }

  ~Matrix() = default;

  constexpr auto operator()(std::size_t i, std::size_t j) -> Type & {
    const size_t page_index = i / page_size;
    const size_t row_in_page = i % page_size;
    return m_pages.at(page_index)[row_in_page * Col + j];
  }

  constexpr auto operator()(std::size_t i, std::size_t j) const
      -> const Type & {
    const size_t page_index = i / page_size;
    const size_t row_in_page = i % page_size;
    return m_pages[page_index][row_in_page * Col + j];
  }

private:
  static constexpr std::size_t page_size = 64;
  std::vector<std::array<Type, page_size>> m_pages{(Row * Col + page_size - 1) /
                                                   page_size};
};

auto main() -> int {
  // Example usage
  auto matrix1 = Matrix<int, 100, 100>();
  auto matrix2 = Matrix<int, 10000, 1000>();

  matrix1(2, 3) = 42;
  matrix2(699, 699) = 73;

  std::cout << matrix2(699, 699) << std::endl;
  {
    Timer t;
    matrix2(699, 699);
  }

  return 0;
}
