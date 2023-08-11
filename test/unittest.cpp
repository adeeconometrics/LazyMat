#include <gtest/gtest.h>

#include "../include/LazyMatrix.hpp"
#include "../include/LazyOps.hpp"
#include "../include/Utils.hpp"

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

  const Matrix<int, 512, 512> M0{make_vmatrix<int, 512, 512>(std::ref(rng_a))};
  const Matrix<int, 512, 512> M1{make_vmatrix<int, 512, 512>(std::ref(rng_b))};

  EXPECT_TRUE(M0 == M0);
  EXPECT_TRUE(M0 != M1); // this is true even when M1 is set to rng_a
}

TEST(BinaryExpr, BinaryOps) {
  const Matrix<float, 3, 3> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<float, 3, 3> M1{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  const Matrix<int, 3, 3> Mod0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  const Matrix<int, 3, 3> Mod1{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  const Matrix<float, 3, 3> EAdd{{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
  const Matrix<float, 3, 3> ESub{{-8, -6, -4}, {-2, 0, 2}, {4, 6, 8}};
  const Matrix<float, 3, 3> EMul{{9, 16, 21}, {24, 25, 24}, {21, 16, 9}};
  const Matrix<int, 3, 3> EMod{{1, 2, 3}, {4, 0, 2}, {1, 0, 0}};

  Matrix<float, 3, 3> Add{};
  Add = M0 + M1;

  Matrix<float, 3, 3> Sub{};
  Sub = M0 - M1;

  Matrix<float, 3, 3> Mul{};
  Mul = M0 * M1;

  Matrix<float, 3, 3> Div{};
  Div = (M0 * M1) / M1;

  Matrix<int, 3, 3> Mod{};
  Mod = Mod0 % Mod1;

  EXPECT_EQ(Add, EAdd);
  EXPECT_EQ(Sub, ESub);
  EXPECT_EQ(Mul, EMul);
  EXPECT_EQ(Div, M0);
  EXPECT_EQ(Mod, EMod);
}

TEST(UnaryExpr, UnaryOps) {
  const Matrix<float, 3, 3> M0{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
  const Matrix<float, 3, 3> ENeg{
      {-1., -2., -3.}, {-4., -5., -6.}, {-7., -8., -9.}};
  const Matrix<float, 3, 3> ELog{{0.0, 0.6931472, 1.0986123},
                                 {1.3862944, 1.609438, 1.7917595},
                                 {1.9459102, 2.0794415, 2.1972246}};

  const Matrix<float, 3, 3> ELog10{{0.0, 0.30103, 0.47712123},
                                   {0.60206, 0.69897, 0.7781513},
                                   {0.845098, 0.90309, 0.9542425}};

  const Matrix<float, 3, 3> ELog2{{0.0, 1.0, 1.5849625},
                                  {2.0, 2.321928, 2.5849626},
                                  {2.807355, 3.0, 3.169925}};

  const Matrix<float, 3, 3> EExp{{2.718282, 7.3890557, 20.085537},
                                 {54.59815, 148.41316, 403.42877},
                                 {1096.6332, 2980.958, 8103.084}};

  const Matrix<float, 3, 3> EExp2{
      {2.0, 4.0, 8.0}, {16.0, 32.0, 64.0}, {128.0, 256.0, 512.0}};

  const Matrix<float, 3, 3> ESqrt{{1.0, 1.4142135, 1.7320508},
                                  {2.0, 2.236068, 2.4494898},
                                  {2.6457512, 2.828427, 3.0}};

  const Matrix<float, 3, 3> ECrbt{{1.0, 1.2599211, 1.4422495},
                                  {1.587401, 1.709976, 1.8171206},
                                  {1.9129312, 2.0, 2.0800838}};

  const Matrix<float, 3, 3> ESin{{0.841471, 0.9092974, 0.14112},
                                 {-0.7568025, -0.9589243, -0.2794155},
                                 {0.6569866, 0.98935825, 0.41211846}};

  const Matrix<float, 3, 3> ECos{{0.5403023, -0.4161468, -0.9899925},
                                 {-0.6536436, 0.28366217, 0.96017027},
                                 {0.75390226, -0.14550003, -0.91113025}};

  const Matrix<float, 3, 3> ETan{{1.5574077, -2.1850398, -0.14254655},
                                 {1.1578213, -3.380515, -0.29100618},
                                 {0.871448, -6.799711, -0.45231566}};

  const Matrix<float, 3, 3> EToDeg{{57.29577951, 114.59155903, 171.88733854},
                                   {229.18311805, 286.47889757, 343.77467708},
                                   {401.07045659, 458.3662361, 515.66201562}};

  const Matrix<float, 3, 3> EToRad{{0.01745329, 0.03490659, 0.05235988},
                                   {0.06981317, 0.08726646, 0.10471976},
                                   {0.12217305, 0.13962634, 0.15707963}};

  Matrix<float, 3, 3> Neg{};
  Neg = -M0;

  Matrix<float, 3, 3> Log{};
  Log = log(M0);

  Matrix<float, 3, 3> Log10{};
  Log10 = log10(M0);

  Matrix<float, 3, 3> Log2{};
  Log2 = log2(M0);

  Matrix<float, 3, 3> Exp{};
  Exp = exp(M0);

  Matrix<float, 3, 3> Exp2{};
  Exp2 = exp2(M0);

  Matrix<float, 3, 3> Sqrt{};
  Sqrt = sqrt(M0);

  Matrix<float, 3, 3> Cbrt{};
  Cbrt = cbrt(M0);

  Matrix<float, 3, 3> Sin{};
  Sin = sin(M0);

  Matrix<float, 3, 3> Cos{};
  Cos = cos(M0);

  Matrix<float, 3, 3> Tan{};
  Tan = tan(M0);

  Matrix<float, 3, 3> Deg{};
  Deg = to_deg(M0);

  Matrix<float, 3, 3> Rad{};
  Rad = to_rad(M0);

  EXPECT_EQ(Neg, ENeg);

  for (std::size_t i = 0; i < 3; i++) {
    for (std::size_t j = 0; j < 3; j++) {
      EXPECT_NEAR(Log(i, j), ELog(i, j), 1e-6);
      EXPECT_NEAR(Log10(i, j), ELog10(i, j), 1e-6);
      EXPECT_NEAR(Log2(i, j), ELog2(i, j), 1e-6);
      EXPECT_NEAR(Exp(i, j), EExp(i, j), 1e-4);
      EXPECT_NEAR(Exp2(i, j), Exp2(i, j), 1e-6);
      EXPECT_NEAR(Sqrt(i, j), ESqrt(i, j), 1e-6);
      EXPECT_NEAR(Cbrt(i, j), ECrbt(i, j), 1e-6);
      EXPECT_NEAR(Sin(i, j), ESin(i, j), 1e-6);
      EXPECT_NEAR(Cos(i, j), ECos(i, j), 1e-6);
      EXPECT_NEAR(Tan(i, j), ETan(i, j), 1e-6);
      EXPECT_NEAR(Deg(i, j), EToDeg(i, j), 1e-6);
      EXPECT_NEAR(Rad(i, j), EToRad(i, j), 1e-6);
    }
  }
}