#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "globals.h"
#include "entity.h"

#define STATUSBAR_INITIAL_HEALTH 3
#define STATUSBAR_MAX_HEALTH 5

class Hearts : public Entity {
  public:
    Hearts() : _fillLevel(STATUSBAR_INITIAL_HEALTH) {}

    virtual void update() {}

    virtual void render() {
      uint8_t frame;
      for (register uint8_t i = 0; i < STATUSBAR_MAX_HEALTH; i++) {
        frame = (i >= this->_fillLevel) ? 1 : 0;
        Sprites::drawPlusMask(this->pos.x + (i * (pgm_read_byte(&heart_plus_mask[0]) + 1)),
                              this->pos.y,
                              heart_plus_mask,
                              frame);
      }
    }

    void setFillLevel(const uint8_t level) {
      this->_fillLevel = level;
    }

  private:
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
      this->renderRAM();
      this->_hearts.render();
      this->renderMeter();
    }

    void renderCPULoad() {
      arduboy.setTextColor(WHITE);
      arduboy.setTextBackground(BLACK);
      arduboy.setCursor(0, 56);
      arduboy.print(arduboy.cpuLoad());
    }

    void renderRAM() {
      extern int __heap_start, *__brkval;
      int v;
      int ram = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
      arduboy.setTextColor(WHITE);
      arduboy.setTextBackground(BLACK);
      arduboy.setCursor(32, 56);
      arduboy.print(ram);
    }

    void renderMeter() {
      arduboy.drawRect(50, 0, 32, 5);
      arduboy.fillRect(51, 1, 30, 3, BLACK);
      static uint8_t level = 0;
      if (++level == 31) level = 0;
      arduboy.drawRect(51, 2, level, 1, WHITE);
    }

    void setHealth(const uint8_t health) {
      this->_hearts.setFillLevel(health);
    }

  private:
    Hearts _hearts;
};

#endif // STATUSBAR_H
