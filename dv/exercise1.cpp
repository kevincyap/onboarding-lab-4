#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>
void checkFunction(uint8_t op) {
  VExercise1 model;
  model.a = 0;
  model.b = 0;
  model.op = op;
  do {
    do {
      model.eval();
      uint8_t result;
      switch (op) {
        case 0:
          result = model.a ^ model.b;
          break;
        case 1:
          result = model.a << model.b;
          if (model.b >= 8) {
            result = 0;
          }
          break;
        case 2: 
          if (model.b == 0) {
            result = 0;
          } else {
            result = model.a % model.b;
          }
          break;
        case 3:
          result = ~(model.a & model.b);
          break;
      }
      REQUIRE(result == model.out);
    } while (++model.b);
  } while (++model.a);
}

TEST_CASE("Exercise 1") {
  checkFunction(0); // ^
  checkFunction(1); // <<
  checkFunction(2); // %
  checkFunction(3); // ~(a & b)
}
