#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
Arduboy2 arduboy;

struct SPoint {
  SPoint() : x(0), y(0) {}
  SPoint(uint8_t x, uint8_t y) : x(x), y(y) {}
  uint8_t x;
  uint8_t y;
};

using FuncPtr = void (*)();

#include "sprites.h"

#endif // GLOBALS_H
