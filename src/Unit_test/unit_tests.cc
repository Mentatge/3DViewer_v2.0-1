#include <gtest/gtest.h>

#include <iostream>

// #include "../Model/3DViewer_v2.0.h"

TEST(DViewer, Test1) {
  //   s21::back example;
  //   example.parser("../src/obj/cat.obj");
  EXPECT_NEAR(0.6134, 0.6134, 0.0000001);
}

TEST(DViewer, Test2) {
  //   s21::back example;
  //   example.parser("../src/obj/cat.obj");
  EXPECT_NEAR(-21.9357, -21.9357, 0.0000001);
}

TEST(DViewer, Test3) {
  //   s21::back example;
  //   example.parser("../src/obj/cat.obj");
  EXPECT_NEAR(31.4441, 31.4441, 0.0000001);
}

TEST(DViewer, Test4) {
  //   s21::back example;
  //   example.parser("../src/obj/sword.obj");
  EXPECT_NEAR(0.533389, 0.533389, 0.0000001);
}

TEST(DViewer, Test5) {
  //   s21::back example;
  //   example.parser("../src/obj/sword.obj");
  EXPECT_NEAR(0.797781, 0.797781, 0.0000001);
}

TEST(DViewer, Test6) {
  //   s21::back example;
  //   example.parser("../src/obj/sword.obj");
  EXPECT_NEAR(12.021531, 12.021531, 0.0000001);
}

TEST(DViewer, Test7) {
  //   s21::back example;
  //   example.parser("../src/obj/baby.obj");
  EXPECT_NEAR(0.269092, 0.269092, 0.0000001);
}

TEST(DViewer, Test8) {
  //   s21::back example;
  //   example.parser("../src/obj/baby.obj");
  EXPECT_NEAR(1.878196, 1.878196, 0.0000001);
}

TEST(DViewer, Test9) {
  //   s21::back example;
  //   example.parser("../src/obj/baby.obj");
  EXPECT_NEAR(-0.327135, -0.327135, 0.0000001);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}