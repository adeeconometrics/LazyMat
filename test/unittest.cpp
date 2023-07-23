#include <gtest/gtest.h>

#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"

using namespace lm;

TEST(BinaryExpr, EqualityOps) {
  const Matrix<int> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int> M1{{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};

  EXPECT_TRUE(M0 == M0);
  EXPECT_TRUE(M1 != M0);
}

TEST(BinaryExpr, BinaryOps) {
  const Matrix<float> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<float> M1{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  const Matrix<float> EAdd{{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
  const Matrix<float> ESub{{-8, -6, -4}, {-2, 0, 2}, {4, 6, 8}};
  const Matrix<float> EMul{{9, 16, 21}, {24, 25, 24}, {21, 16, 9}};

  Matrix<float> Add(3, 3);
  Add = M0 + M1;

  Matrix<float> Sub(3, 3);
  Sub = M0 - M1;

  Matrix<float> Mul(3, 3);
  Mul = M0 * M1;

  Matrix<float> Div(3, 3);
  Div = (M0 * M1) / M1;

  EXPECT_EQ(Add, EAdd);
  EXPECT_EQ(Sub, ESub);
  EXPECT_EQ(Mul, EMul);
  EXPECT_EQ(Div, M0);
}

TEST(UnaryExpr, UnaryOps) {
  const Matrix<float> M0{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  const Matrix<float> ENeg{{-1., -2., -3.}, {-4., -5., -6.}, {-7., -8., -9.}};
  const Matrix<float> ELog{
      {0.0, 0.6931471805599453, 1.0986122886681098},
      {1.3862943611198906, 1.6094379124341003, 1.791759469228055},
      {1.9459101490553132, 2.0794415416798357, 2.1972245773362196}};
  const Matrix<float> ELog10{
      {0.0, 0.3010299956639812, 0.47712125471966244},
      {0.6020599913279624, 0.6989700043360189, 0.7781512503836436},
      {0.8450980400142568, 0.9030899869919435, 0.9542425094393249}};

  const Matrix<float> ELog2{{{0.0, 1.0, 1.584962500721156},
                             {2.0, 2.321928094887362, 2.584962500721156},
                             {2.807354922057604, 3.0, 3.169925001442312}}};

  Matrix<float> Neg(3, 3);
  Neg = -M0;

  Matrix<float> Log(3, 3);
  Log = log(M0);

  Matrix<float> Log10(3, 3);
  Log = log10(M0);

  Matrix<float> Log2(3, 3);
  Log = log2(M0);

  EXPECT_EQ(Neg, ENeg);

  const std::size_t rows = M0.rows();
  const std::size_t cols = M0.cols();

  for (std::size_t i = 0; i < rows; i++) {
    for (std::size_t j = 0; j < cols; j++) {
      // ASSERT_DOUBLE_EQ(Log[i][j], ELog[i][j]) << Log;
      ASSERT_DOUBLE_EQ(Log10[i][j], ELog10[i][j]) << i << ", " << j;
      ASSERT_DOUBLE_EQ(Log2[i][j], ELog2[i][j]) << i << ", " << j;
    }
  }
}