# Outline

Contains API outline to be implemented

```cpp
template <typename T>
constexpr auto unary_fn(const Mat<T>&, const std::functional<Mat<T>(Mat<T>)>&) -> OpNode;
template <typename T>
constexpr auto unary_fn(const OpNode&, const std::functional<T(T)>&) -> OpNode;

```
