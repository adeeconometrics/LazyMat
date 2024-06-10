#include <gtest/gtest.h>

#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"

#include <iostream>
#include <random>

using namespace lm;

TEST(BinaryExpr, EqualityOps) {
  const Matrix<int, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int, 3, 3> M1{{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};

  EXPECT_TRUE(M0 == M0);
  EXPECT_TRUE(M1 != M0);
}

TEST(BinaryExprLargeMat, EqualityOps) {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  const std::size_t M = 3;
  const std::size_t N = 3;

  const Matrix<int, M, N> M0{make_vmatrix<int, M, N>(std::ref(rng_a))};
  const Matrix<int, M, N> M1{make_vmatrix<int, M, N>(std::ref(rng_b))};

  std::mt19937 rng_a2(64);
  std::mt19937 rng_b2(65);

  const auto N0 = Matrix<int, M, N>{make_vmatrix<int, M, N>(std::ref(rng_a2))};
  const auto N1 = Matrix<int, M, N>{make_vmatrix<int, M, N>(std::ref(rng_b2))};

  EXPECT_TRUE(M0 == N0);
  EXPECT_TRUE(M0 != N1); // this is true even when M1 is set to rng_a

  EXPECT_FALSE(M0 == M1);
  EXPECT_FALSE(M0 != M0);
}

TEST(BinaryExpr, BinaryOps) {
  const Matrix<int, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int, 3, 3> M1{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  const auto EAdd = M0 + M1;
  const auto ESub = M0 - M1;
  const auto EMul = M0 * M1;
  const auto EDiv = M0 / M1;
  const auto EMod = M0 % M1;

  for (std::size_t i = 0; i < 3; i++) {
    for (std::size_t j = 0; j < 3; j++) {
      EXPECT_EQ(EAdd(i, j), M0(i, j) + M1(i, j));
      EXPECT_EQ(ESub(i, j), M0(i, j) - M1(i, j));
      EXPECT_EQ(EMul(i, j), M0(i, j) * M1(i, j));
      EXPECT_EQ(EDiv(i, j), M0(i, j) / M1(i, j));
      EXPECT_EQ(EMod(i, j), M0(i, j) % M1(i, j));
    }
  }
}

TEST(BinaryExpr, BinaryOpsScalar) {
  const Matrix<int, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  const int scalar = 2;

  const auto EAdd = M0 + scalar;
  const auto EAddRhs = scalar + M0;
  const auto ESub = M0 - scalar;
  const auto ESubRhs = scalar - M0;
  const auto EMul = M0 * scalar;
  const auto EMulRhs = scalar * M0;
  const auto EDiv = M0 / scalar;
  const auto EDivRhs = scalar / M0;
  const auto EMod = M0 % scalar;
  const auto EModRhs = scalar % M0;

  for (std::size_t i = 0; i < 3; i++) {
    for (std::size_t j = 0; j < 3; j++) {
      EXPECT_EQ(EAdd(i, j), M0(i, j) + scalar);
      EXPECT_EQ(EAddRhs(i, j), scalar + M0(i, j));

      EXPECT_EQ(ESub(i, j), M0(i, j) - scalar);
      EXPECT_EQ(ESubRhs(i, j), scalar - M0(i, j));

      EXPECT_EQ(EMul(i, j), M0(i, j) * scalar);
      EXPECT_EQ(EMulRhs(i, j), scalar * M0(i, j));

      EXPECT_EQ(EDiv(i, j), M0(i, j) / scalar);
      EXPECT_EQ(EDivRhs(i, j), scalar / M0(i, j));

      EXPECT_EQ(EMod(i, j), M0(i, j) % scalar);
      EXPECT_EQ(EModRhs(i, j), scalar % M0(i, j));
    }
  }
}

TEST(UnaryExpr, UnaryOps) {
  const Matrix<float, 3, 3> M0{{.1, .2, .3}, {.4, .5, .6}, {.7, .8, .9}};
  const Matrix<float, 3, 3> M1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  const auto ENeg = -M0;
  const auto ELog = log(M0);
  const auto ELog10 = log10(M0);
  const auto ELog2 = log2(M0);
  const auto EExp = exp(M0);
  const auto EExp2 = exp2(M0);
  const auto ESqrt = sqrt(M0);
  const auto ECBrt = cbrt(M0);

  const auto ESin = sin(M0);
  const auto ECos = cos(M0);
  const auto ETan = tan(M0);

  const auto EAsin = asin(M0);
  const auto EAcos = acos(M0);
  const auto EAtan = atan(M0);

  const auto Esinh = sinh(M0);
  const auto Ecosh = cosh(M0);
  const auto Etanh = tanh(M0);

  const auto EAsinh = asinh(M1);
  const auto EAcosh = acosh(M1);
  const auto EAtanh = atanh(M1);

  // const auto E

  for (std::size_t i = 0; i < 3; i++) {
    for (std::size_t j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(ENeg(i, j), -M0(i, j));
      EXPECT_DOUBLE_EQ(ELog(i, j), std::log(M0(i, j)));
      EXPECT_DOUBLE_EQ(ELog10(i, j), std::log10(M0(i, j)));
      EXPECT_DOUBLE_EQ(ELog2(i, j), std::log2(M0(i, j)));
      EXPECT_DOUBLE_EQ(EExp(i, j), std::exp(M0(i, j)));
      EXPECT_DOUBLE_EQ(EExp2(i, j), std::exp2(M0(i, j)));
      EXPECT_DOUBLE_EQ(ESqrt(i, j), std::sqrt(M0(i, j)));
      EXPECT_DOUBLE_EQ(ECBrt(i, j), std::cbrt(M0(i, j)));

      EXPECT_DOUBLE_EQ(ESin(i, j), std::sin(M0(i, j)));
      EXPECT_DOUBLE_EQ(ECos(i, j), std::cos(M0(i, j)));
      EXPECT_DOUBLE_EQ(ETan(i, j), std::tan(M0(i, j)));

      EXPECT_DOUBLE_EQ(EAsin(i, j), std::asin(M0(i, j)));
      EXPECT_DOUBLE_EQ(EAcos(i, j), std::acos(M0(i, j)));
      EXPECT_DOUBLE_EQ(EAtan(i, j), std::atan(M0(i, j)));

      EXPECT_DOUBLE_EQ(Esinh(i, j), std::sinh(M0(i, j)));
      EXPECT_DOUBLE_EQ(Ecosh(i, j), std::cosh(M0(i, j)));
      EXPECT_DOUBLE_EQ(Etanh(i, j), std::tanh(M0(i, j)));

      EXPECT_DOUBLE_EQ(EAsinh(i, j), std::asinh(M1(i, j)));
      // EXPECT_DOUBLE_EQ(EAcosh(i, j), std::acosh(M1(i, j)));
      EXPECT_DOUBLE_EQ(EAtanh(i, j), std::atanh(M1(i, j)));
    }
  }
}

TEST(UnaryExpr, UnaryOpsHelper) {
  const Matrix<float, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  const auto EToRad = to_rad(M0);
  const auto EToDeg = to_deg(EToRad);

  for (std::size_t i = 0; i < 3; i++) {
    for (std::size_t j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(EToRad(i, j), M0(i, j) * M_PI / 180);
      EXPECT_DOUBLE_EQ(EToDeg(i, j), M0(i, j));
    }
  }
}

TEST(TestMatMulExpr, MatMul) {
  const Matrix<float, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<float, 3, 3> M1{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  const Matrix<float, 3, 3> EMul{{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};

  Matrix<float, 3, 3> Mul{};
  Mul = matmul(M0, M1);

  EXPECT_EQ(Mul, EMul);
}
/**
 * @brief WARNING: Implementation matmul suffers from precision loss for large
 * matrices (over 32x32). Summation algorithm that might be worth looking into:
 * Kahan summation algorithm
 * (https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
 *
 */
TEST(TestMatMulExpr, MatMulLarge) {
  std::mt19937 rng_a(64);
  std::mt19937 rng_b(65);

  const std::size_t M = 32;
  const std::size_t N = 32;

  const Matrix<double, M, N> M0{make_vmatrix<double, M, N>(std::ref(rng_a))};
  const Matrix<double, M, N> M1{make_vmatrix<double, M, N>(std::ref(rng_b))};

  Matrix<double, M, N> Mul{};
  Mul = matmul(M0, M1);

  for (std::size_t i = 0; i < 32; i++) {
    for (std::size_t j = 0; j < 32; j++) {
      double sum = 0;
      for (std::size_t k = 0; k < 32; k++) {
        sum += M0(i, k) * M1(k, j);
      }
      EXPECT_DOUBLE_EQ(Mul(i, j), sum);
    }
  }
}

TEST(Parser, UnaryParser) {}