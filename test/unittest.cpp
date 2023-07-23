#include <gtest/gtest.h>

#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"

using namespace lm;

TEST(EqualityOps, BinaryExpr) {
  const Matrix<int> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int> M1{{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};

  EXPECT_TRUE(M0 == M0);
  EXPECT_TRUE(M1 != M0);
}