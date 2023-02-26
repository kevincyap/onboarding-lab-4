#include <catch2/catch_test_macros.hpp>
#include <VExercise4.h>

TEST_CASE("Exercise 4") {
  VExercise4 model;
  uint8_t a, b, g;
  a = 3;
  b = 1;
  g = 2;
  model.alpha = a;
  model.beta = b;
  model.gamma = g;
  
  model.cs = 0;
  for (int i = 0; i < 4; ++i) {
    model.sel = i;
    model.eval();
    REQUIRE(model.out == 0);
  }

  model.cs = 1;
  for (int i = 0; i < 4; ++i) {
    model.sel = i;
    model.eval();
    switch (i) {
      case 0:
        REQUIRE(model.out == a);
        break;
      case 1:
        REQUIRE(model.out == b);
        break;
      case 2:
        REQUIRE(model.out == g);
        break;
      case 3:
        REQUIRE(model.out == (a & (b | g)));
        break;
    }
  }
}
