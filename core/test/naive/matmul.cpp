#include "core/test/common/matmul.h"

#include "core/base/include/ndArray.h"
#include "core/op/naive/ops.h"
#include "core/test/common/factory.h"
#include "core/test/common/utils.h"
#include "gtest/gtest.h"

using namespace nncore;
using namespace test;
using namespace opr;
using namespace opr::naive;

using F = NDArrayFactory;

TEST(Naive, Matmul) {
  OpNaiveImpl<int> oprs;

  // Group 1
  NDArray a1 = F::from_list({1, 2, 3, 4, 5, 6}, {2, 3}, dtype::Int32());
  NDArray b1 = F::from_list({-1, 1, 2, 1, -1, 3}, {3, 2}, dtype::Int32());
  NDArray truth1 = F::from_list({0, 12, 0, 27}, {2, 2}, dtype::Int32());
  NDArray pred1 = F::empty({2, 2}, dtype::Int32());

  using Param = param::matmul;
  Param p1;

  oprs.matmul(a1, b1, pred1, p1);
  assert_same_data<int>(pred1, truth1, 0.0001f);

  // Group 2
  NDArray a2 = F::from_list({1, 3, 5, 7, 9}, {5, 1}, dtype::Int32());
  NDArray b2 = F::from_list({2, 4, 6, 8, 10}, {1, 5}, dtype::Int32());
  NDArray truth2 =
      F::from_list({2,  4,  6,  8,  10, 6,  12, 18, 24, 30, 10, 20, 30,
                    40, 50, 14, 28, 42, 56, 70, 18, 36, 54, 72, 90},
                   {5, 5}, dtype::Int32());
  NDArray pred2 = F::empty({5, 5}, dtype::Int32());

  using Param = param::matmul;
  Param p2;

  oprs.matmul(a2, b2, pred2, p2);

  assert_same_data<int>(pred2, truth2, 0.0001f);

  // Group 4
  NDArray a4 = F::from_list({1, 2, 5, -2, -4, 6, 1, 2, 5, -2, -4, 6,
                             1, 2, 5, -2, -4, 6, 1, 2, 5, -2, -4, 6},
                            {1, 4, 2, 3}, dtype::Int32());
  NDArray b4 = F::from_list({1, 1, 2, 3, -2, -4, 8, 15, -7, -1, 5, 0},
                            {1, 4, 3, 1}, dtype::Int32());
  NDArray truth4 = F::from_list({13, 6, -21, -22, 3, -118, 9, -18},
                                {1, 4, 2, 1}, dtype::Int32());
  NDArray pred4 = F::empty({1, 4, 2, 1}, dtype::Int32());

  using Param = param::matmul;
  Param p4;

  oprs.matmul(a4, b4, pred4, p4);

  assert_same_data<int>(pred4, truth4, 0.0001f);

  // Group 3
  NDArray a3 = F::from_list(
      {-7,  8,   -11, 11,  14,  6,   8,   9,   -7,  -17, 2,  -10, 10,  -12, 11,
       6,   -9,  13,  7,   -12, 17,  -8,  -2,  -18, -18, 19, -11, -18, -11, -11,
       -20, -4,  -6,  19,  -11, -18, -3,  6,   -19, 10,  -8, -17, -20, 9,   -3,
       -19, 1,   2,   14,  6,   11,  -8,  -14, 2,   0,   11, 9,   -2,  7,   4,
       -19, -4,  19,  5,   11,  -13, -6,  -16, 19,  -15, 11, -5,  -2,  10,  10,
       -6,  11,  13,  -5,  19,  8,   -12, 3,   8,   19,  4,  -20, 7,   13,  -15,
       -18, 7,   -2,  -11, 19,  -16, 8,   13,  -18, -1,  12, 14,  -14, -8,  14,
       12,  -16, 15,  -16, -15, -20, 4,   -19, -19, 3,   12, 1,   -13, -8,  16},
      {2, 3, 4, 5}, dtype::Int32());
  NDArray b3 = F::from_list(
      {-14, -8,  4,   16,  5,   2,   9,   -7,  -16, 1,   -16, -3,  8,   1,
       -1,  -3,  0,   -29, -28, 22,  11,  3,   -29, 3,   -21, -6,  4,   -22,
       14,  7,   17,  -17, 2,   -17, -10, -7,  0,   -3,  10,  -12, 15,  16,
       -9,  -26, 24,  -13, -23, 21,  -13, 3,   -27, -12, -2,  -30, 4,   -8,
       -7,  -16, -15, -30, -3,  -17, -9,  14,  25,  -22, -6,  0,   4,   -4,
       -29, -24, 0,   -12, 28,  -24, -7,  -21, 9,   -7,  -18, -2,  11,  2,
       24,  4,   8,   -28, -19, 20,  -15, -6,  -30, 18,  8,   27,  -13, -6,
       -13, 11,  18,  24,  -25, 0,   -14, 20,  -20, -28, -13, 0,   -8,  -29,
       -23, 21,  13,  5,   -29, -18, -25, -20, -9,  -6,  26,  27,  16,  20,
       3,   28,  -10, -10, -11, -4,  21,  28,  -6,  10,  26,  28,  28,  -6,
       17,  9,   21,  -16, -10, -12, -7,  21,  16,  15,  24,  -4,  13,  -30,
       18,  -6,  2,   14,  28,  0,   10,  15,  5,   -27, -7,  27,  -24, 14,
       -23, 11,  -13, 2,   -9,  -23, -24, -29, -30, 8,   0,   -29, 22,  -17,
       -13, -16, -14, -15, 21,  -1,  25,  16,  -8,  0,   -19, 28,  -2,  -24,
       15,  -22, 25,  27,  -20, 0,   10,  -19, 28,  -7,  -29, -30, -26, -6,
       4,   -26, -28, 14,  -22, 9,   -30, -16, -4,  -18, 18,  -2,  9,   -17,
       -5,  22,  23,  4,   28,  20,  20,  -6,  -2,  18,  11,  9,   0,   -16,
       -8,  2},
      {2, 3, 5, 8}, dtype::Int32());
  NDArray truth3 = F::from_list(
      {-233, 79,    56,   -718,  62,    -4,   575,   -363,  -99,  30,   -214,
       543,  95,    49,   -504,  284,   406,  -431,  -270,  469,  -128, -93,
       -356, 118,   -111, -272,  -48,   339,  199,   127,   -315, 49,   -77,
       892,  -303,  146,  484,   503,   -45,  951,   279,   933,  154,  442,
       565,  664,   -99,  576,   269,   -522, -44,   1012,  -301, 637,  -152,
       -851, -748,  -95,  547,   84,    -590, 88,    989,   116,  670,  -87,
       208,  -401,  -72,  -764,  303,   -436, -37,   452,   -452, -384, -806,
       -118, -456,  33,   108,   -58,   383,  -140,  226,   -436, 358,  -582,
       -533, 394,   -76,  -230,  -249,  86,   54,    -348,  798,  296,  245,
       -572, 37,    -92,  794,   -896,  -624, -88,   -1123, 258,  -332, -497,
       -303, -244,  -71,  -492,  395,   479,  217,   352,   541,  250,  579,
       -220, 464,   -503, 314,   496,   601,  -246,  -207,  424,  326,  -791,
       603,  151,   468,  925,   393,   -719, 583,   -4,    406,  987,  -186,
       119,  -488,  488,  -450,  113,   29,   -1207, 853,   90,   -463, 194,
       -560, 113,   -139, -1103, 142,   -691, -172,  216,   202,  -246, -532,
       -244, -1054, 80,   -164,  -766,  -537, -281,  606,   -418, -61,  -693,
       955,  -84,   -512, 569,   -1546, -194, -83,   1079,  132,  314,  168,
       92,   -150,  -460, -775,  -50},
      {2, 3, 4, 8}, dtype::Int32());
  NDArray pred3 = F::empty({2, 3, 4, 8}, dtype::Int32());

  using Param = param::matmul;
  Param p3;

  oprs.matmul(a3, b3, pred3, p3);

  assert_same_data<int>(pred3, truth3, 0.0001f);
}