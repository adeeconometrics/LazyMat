#include <array>
#include <iostream>
#include <memory>
#include <type_traits>

template <typename Type, std::size_t Row, std::size_t Col, typename = void>
class Matrix {
public:
  Matrix() { std::cout << "default is called\n"; };

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
  using Container = std::array<Type, Col * Row>;
  using Page = std::unique_ptr<Container>;

  Matrix() {
    for (std::size_t i = 0; i < m_pages.size(); ++i) {
      m_pages[i] = std::make_unique<Container>();
    }
    std::cout << "overload is called\n";
  }

  ~Matrix() = default;

  auto operator()(std::size_t i, std::size_t j) -> Type & {
    const size_t page_index = i / page_size;
    const size_t row_in_page = i % page_size;
    return (*m_pages[page_index])[row_in_page * Col + j];
  }

  auto operator()(std::size_t i, std::size_t j) const -> const Type & {
    const size_t page_index = i / page_size;
    const size_t row_in_page = i % page_size;
    return (*m_pages[page_index])[row_in_page * Col + j];
  }

private:
  static constexpr std::size_t page_size = 256;
  std::array<Page, (Row * Col + page_size - 1) / page_size> m_pages;
};

auto main() -> int {
  // Example usage
  auto matrix1 = Matrix<int, 100, 100>();
  auto matrix2 = Matrix<int, 300, 300>();

  matrix1(2, 3) = 42;
  matrix2(299, 299) = 73;

  std::cout << matrix1(2, 3) << std::endl;
  std::cout << matrix2(299, 299) << std::endl;

  return 0;
}
