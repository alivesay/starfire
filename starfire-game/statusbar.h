#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "globals.h"
#include "entity.h"

#define STATUSBAR_INITIAL_HEALTH 3
#define STATUSBAR_MAX_HEALTH 5

class Hearts : public Entity {
  public:
    Hearts() :
    _bitmap(heart_bitmap),
    _bitmapMask(heart_mask),
    _fillLevel(STATUSBAR_INITIAL_HEALTH) {}

    virtual void update() {}

    virtual void render() {
      uint8_t frame;
      for (register uint8_t i = 0; i < STATUSBAR_MAX_HEALTH; i++) {
        frame = (i >= this->_fillLevel) ? 1 : 0;
        Sprites::drawExternalMask(this->getX() + (i * (pgm_read_byte(&heart_bitmap[0]) + 1)),
                                  this->getY(),
                                  this->_bitmap,
                                  this->_bitmapMask,
                                  frame,
                                  frame);
      }
    }

    void setFillLevel(const uint8_t level) {
      this->_fillLevel = level;
    }

  private:
    uint8_t* _bitmap;
    uint8_t* _bitmapMask;
    uint8_t _fillLevel;
};

class StatusBar : public Entity {
  public:
    StatusBar() {}

    virtual void update() {
      this->_hearts.update();
    }

    virtual void render() {
      this->renderCPULoad();
      this->_hearts.render();
    }

    void renderCPULoad() {
      arduboy.setTextColor(WHITE);
      arduboy.setTextBackground(BLACK);
      arduboy.setCursor(0, 56);
      arduboy.print(arduboy.cpuLoad());
    }

    void setHealth(const uint8_t health) {
      this->_hearts.setFillLevel(health);
    }

  private:
    Hearts _hearts;
};

#endif // STATUSBAR_H
