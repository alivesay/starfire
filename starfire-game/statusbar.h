#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "globals.h"
#include "entity.h"

#define STATUSBAR_MAX_HEARTS 4

class Heart : public Entity {
  public:
    Heart() :
    _bitmap(heart_bitmap),
    _bitmapMask(heart_mask) {}

    virtual void update() {}

    virtual void render() {
      for (register uint8_t i = 0; i < STATUSBAR_MAX_HEARTS; i++) {

        Sprites::drawExternalMask(this->getX() + (i * pgm_read_byte(&heart_bitmap[0]) + 1),
                                  this->getY(),
                                  this->_bitmap,
                                  this->_bitmapMask,
                                  0,
                                  0);
      }
    }

  private:
    uint8_t* _bitmap;
    uint8_t* _bitmapMask;
};

class StatusBar : public Entity {
  public:
    StatusBar() {}

    virtual void update() {}

    virtual void render() {
      arduboy.setTextColor(WHITE);
      arduboy.setTextBackground(BLACK);
      arduboy.setCursor(0, 56);
      arduboy.print(arduboy.cpuLoad());
      this->_heart.render();
    }

  private:
    Heart _heart;
};

#endif // STATUSBAR_H
