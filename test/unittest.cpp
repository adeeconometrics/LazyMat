#include <gtest/gtest.h>

#include "../include/LazyExpr.hpp"
#include "../include/LazyMatrix.hpp"
#include "../include/Utils.hpp"

#include <iostream>

// using namespace lm;

// TEST(BinaryExpr, EqualityOps) {
//   const Matrix<int> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//   const Matrix<int> M1{{1, 2, 3}, {4, 5, 6}, {7, 8, 10}};

//   EXPECT_TRUE(M0 == M0);
//   EXPECT_TRUE(M1 != M0);
// }

// TEST(BinaryExpr, BinaryOps) {
//   const Matrix<float> M0{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//   const Matrix<float> M1{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

//   const Matrix<float> EAdd{{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
//   const Matrix<float> ESub{{-8, -6, -4}, {-2, 0, 2}, {4, 6, 8}};
//   const Matrix<float> EMul{{9, 16, 21}, {24, 25, 24}, {21, 16, 9}};

//   Matrix<float> Add(3, 3);
//   Add = M0 + M1;

//   Matrix<float> Sub(3, 3);
//   Sub = M0 - M1;

//   Matrix<float> Mul(3, 3);
//   Mul = M0 * M1;

//   Matrix<float> Div(3, 3);
//   Div = (M0 * M1) / M1;

//   EXPECT_EQ(Add, EAdd);
//   EXPECT_EQ(Sub, ESub);
//   EXPECT_EQ(Mul, EMul);
//   EXPECT_EQ(Div, M0);
// }

// TEST(UnaryExpr, UnaryOps) {
//   const Matrix<float> M0{{1., 2., 3.}, {4., 5., 6.}, {7., 8., 9.}};
//   const Matrix<float> ENeg{{-1., -2., -3.}, {-4., -5., -6.}, {-7., -8.,
//   -9.}}; const Matrix<float> ELog{{0.0, 0.6931472, 1.0986123},
//                            {1.3862944, 1.609438, 1.7917595},
//                            {1.9459102, 2.0794415, 2.1972246}};

//   const Matrix<float> ELog10{{0.0, 0.30103, 0.47712123},
//                              {0.60206, 0.69897, 0.7781513},
//                              {0.845098, 0.90309, 0.9542425}};

//   const Matrix<float> ELog2{{0.0, 1.0, 1.5849625},
//                             {2.0, 2.321928, 2.5849626},
//                             {2.807355, 3.0, 3.169925}};

//   const Matrix<float> EExp{{2.718282, 7.3890557, 20.085537},
//                            {54.59815, 148.41316, 403.42877},
//                            {1096.6332, 2980.958, 8103.084}};

//   const Matrix<float> EExp2{
//       {2.0, 4.0, 8.0}, {16.0, 32.0, 64.0}, {128.0, 256.0, 512.0}};

//   const Matrix<float> ESqrt{{1.0, 1.4142135, 1.7320508},
//                             {2.0, 2.236068, 2.4494898},
//                             {2.6457512, 2.828427, 3.0}};

//   const Matrix<float> ECrbt{{1.0, 1.2599211, 1.4422495},
//                             {1.587401, 1.709976, 1.8171206},
//                             {1.9129312, 2.0, 2.0800838}};

//   const Matrix<float> ESin{{0.841471, 0.9092974, 0.14112},
//                            {-0.7568025, -0.9589243, -0.2794155},
//                            {0.6569866, 0.98935825, 0.41211846}};

//   const Matrix<float> ECos{{0.5403023, -0.4161468, -0.9899925},
//                            {-0.6536436, 0.28366217, 0.96017027},
//                            {0.75390226, -0.14550003, -0.91113025}};

//   const Matrix<float> ETan{{1.5574077, -2.1850398, -0.14254655},
//                            {1.1578213, -3.380515, -0.29100618},
//                            {0.871448, -6.799711, -0.45231566}};

//   Matrix<float> Neg(3, 3);
//   Neg = -M0;

//   Matrix<float> Log(3, 3);
//   Log = log(M0);

//   Matrix<float> Log10(3, 3);
//   Log10 = log10(M0);

//   Matrix<float> Log2(3, 3);
//   Log2 = log2(M0);

//   Matrix<float> Exp(3, 3);
//   Exp = exp(M0);

//   Matrix<float> Exp2(3, 3);
//   Exp2 = exp2(M0);

//   Matrix<float> Sqrt(3, 3);
//   Sqrt = sqrt(M0);

//   Matrix<float> Cbrt(3, 3);
//   Cbrt = cbrt(M0);

//   Matrix<float> Sin(3, 3);
//   Sin = sin(M0);

//   Matrix<float> Cos(3, 3);
//   Cos = cos(M0);

//   Matrix<float,3,3> Tan(3, 3);
//   Tan = tan(M0);

//   EXPECT_EQ(Neg, ENeg);

//   const std::size_t rows = M0.rows();
//   const std::size_t cols = M0.cols();

//   for (std::size_t i = 0; i < rows; i++) {
//     for (std::size_t j = 0; j < cols; j++) {
//       EXPECT_NEAR(Log[i][j], ELog[i][j], 1e-6);
//       EXPECT_NEAR(Log10[i][j], ELog10[i][j], 1e-6);
//       EXPECT_NEAR(Log2[i][j], ELog2[i][j], 1e-6);
//       EXPECT_NEAR(Exp[i][j], EExp[i][j], 1e-4);
//       EXPECT_NEAR(Exp2[i][j], Exp2[i][j], 1e-6);
//       EXPECT_NEAR(Sqrt[i][j], ESqrt[i][j], 1e-6);
//       EXPECT_NEAR(Cbrt[i][j], ECrbt[i][j], 1e-6);
//       EXPECT_NEAR(Sin[i][j], ESin[i][j], 1e-6);
//       EXPECT_NEAR(Cos[i][j], ECos[i][j], 1e-6);
//       EXPECT_NEAR(Tan[i][j], ETan[i][j], 1e-6);
//     }
//   }
// }