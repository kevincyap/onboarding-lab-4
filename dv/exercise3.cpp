#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>
uint16_t eval_step(VExercise3& model, uint8_t a, uint16_t b, uint16_t c, bool reset) {
  model.a = a;
  model.b = b;
  model.c = c;
  model.reset = reset;
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
  return model.out;
}

uint8_t Mystery1(uint8_t a, uint16_t b, uint16_t c) {
  uint8_t d = 0;
  switch (a) {
    case 0: 
      d = ((b & 0b111) << 3) | (c & 0b111);
      break;
    case 1:
      d = (1 << 6) | ((c & 0b111) << 3) | (b & 0b111);
      break;
    case 2:
      d = b;
      break;
    case 3:
      d = c;
      break;
  }
  return d;
}
class Mystery2 {
  uint16_t value;
  size_t state;
public: 
  uint16_t eval(uint8_t a, uint16_t b, uint16_t c, bool reset) {
    uint8_t a_in = Mystery1((a&0b11), (b & 0xff), (c & 0xff));
    uint8_t b_in = Mystery1((a>>2)&0b11, (b>>8), (c>>8));
    if (reset) {
      value = ((b_in) << 8) | (a_in);
      state = 0;
    } else {
      switch (state) {
        case 0: 
          value = (a_in << 8) | value & 0xff;
          break;
        case 1:
          value = (value & 0xff00) | b_in;
          break;
        case 2:
          value = ((value & 0xff) << 8) | ((value & 0xff00) >> 8);
          break;
        case 3:
          value = (value & 0xf) << 12 | (value & 0xf0) << 4 | (value & 0xf00) >> 4 | (value & 0xf000) >> 12;
          break;
        case 4:
          uint16_t newVal = value & 1;
          while (value > 0) {
            value = value >> 1;
            newVal = newVal ^ (value & 1);
          }
          value = newVal;
          break;
      }
      state = (state + 1) % 5;
    }
    return value;
  }
};

TEST_CASE("Exercise 3") {
  VExercise3 model;
  Mystery2 mystery;
  uint16_t mval, tval, a, b, c;
  int i = 30;
  int reset = 1;

  do {
    a = rand() & 0xffff;
    b = rand() & 0xffff;
    c = rand() & 0xffff;
    mval = eval_step (model, a, b, c, reset);
    tval = mystery.eval(a, b, c, reset);
    reset = 0;
    REQUIRE(mval == tval);
  } while(--i);
}
