#include <gtest/gtest.h>

#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"
#include "../include/Utils.hpp"

#include <random>

using namespace lm;

TEST(BinaryExpr, EqualityOps) {
  const Matrix<int, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int, 3, 3> M1{{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};

  EXPECT_TRUE(M0 == M0);
  EXPECT_TRUE(M1 != M0);
}

// TEST(BinaryExprLargeMat, EqualityOps) {
//   std::mt19937 rng_a(64);
//   std::mt19937 rng_b(65);

//   const Matrix<int, 16, 16> M0{make_vmatrix<int, 16,
//   16>(std::ref(rng_a))}; const Matrix<int, 16, 16> M1{make_vmatrix<int,
//   16, 16>(std::ref(rng_b))};

//   EXPECT_TRUE(M0 == M0);
//   EXPECT_TRUE(M0 != M1); // this is true even when M1 is set to rng_a
// }

// TEST(BinaryExpr, BinaryOps) {
//   const auto M0 = Matrix<float, 3, 3>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//   const auto M1 = Matrix<float, 3, 3>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

//   const auto N1 = Matrix<int, 3, 3>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
//   const auto N2 = Matrix<int, 3, 3>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

//   for (std::size_t i = 0; i < 3; i++) {
//     for (std::size_t j = 0; j < 3; j++) {
//       EXPECT_DOUBLE_EQ(M0(i, j) + M1(i, j), 10);
//       EXPECT_DOUBLE_EQ(M0(i, j) - M1(i, j), -8);
//       EXPECT_DOUBLE_EQ(M0(i, j) * M1(i, j), 10);
//       EXPECT_DOUBLE_EQ(M0(i, j) / M1(i, j), 1.0 / 9);
//       EXPECT_EQ(N1(i, j) % N2(i, j), 1);
//     }
//   }
// }

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

  const Matrix<double, 32, 32> M0{
      make_vmatrix<double, 32, 32>(std::ref(rng_a))};
  const Matrix<double, 32, 32> M1{
      make_vmatrix<double, 32, 32>(std::ref(rng_b))};

  Matrix<double, 32, 32> Mul{};
  Mul = matmul(M0, M1);

  for (std::size_t i = 0; i < 32; i++) {
    for (std::size_t j = 0; j < 32; j++) {
      double sum = 0;
      for (std::size_t k = 0; k < 32; k++) {
        sum += M0(i, k) * M1(k, j);
      }
      EXPECT_NEAR(Mul(i, j), sum, 1e-6);
    }
  }
}