#ifndef __EAGER_H__
#define __EAGER_H__

// contains eager matrix execution

#include <algorithm>
#include <functional>
#include <vector>

namespace lm {

using std::vector;
using EMat = vector<vector<float>>;

auto operator+(const vector<float> &lhs, const vector<float> &rhs)
    -> vector<float> {
  vector<float> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::plus<>{});
  return result;
}

auto operator*(const vector<float> &lhs, const vector<float> &rhs)
    -> vector<float> {
  vector<float> result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::multiplies<>{});
  return result;
}

auto operator+(const EMat &lhs, const EMat &rhs) -> EMat {
  EMat result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::plus<vector<float>>{});
  return result;
}

auto operator*(const EMat &lhs, const EMat &rhs) -> EMat {
  EMat result;
  result.reserve(lhs.size());
  std::transform(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs),
                 std::back_inserter(result), std::multiplies<vector<float>>{});
  return result;
}
} // namespace lm
#endif // __EAGER_H__