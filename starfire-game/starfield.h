#ifndef STARFIELD_H
#define STARFIELD_H

#include <Arduboy2.h>

#define STARFIELD_PARALLAX_LEVELS 4
#define STARFIELD_PARALLAX_RATES {1, 2, 4, 8}
#define STARFIELD_PARALLAX_COUNTS {50, 30, 20, 10}
#define STARFIELD_NUM_STARS 110

class Starfield {
  private:
    Point _stars[STARFIELD_NUM_STARS];
    const uint8_t _parallax_rates[STARFIELD_PARALLAX_LEVELS] = STARFIELD_PARALLAX_RATES;
    const uint8_t _parallax_counts[STARFIELD_PARALLAX_LEVELS] = STARFIELD_PARALLAX_COUNTS;

  public:
    Starfield() {
      for (int i = 0; i < STARFIELD_NUM_STARS; i++) {
        this->_stars[i].x = random(WIDTH);
        this->_stars[i].y = random(HEIGHT);
      }
    }

    void render() {
      uint16_t si = 0;

      for (register int plevel = 0; plevel < STARFIELD_PARALLAX_LEVELS; plevel++) {
        for (register int scount = 0; scount < this->_parallax_counts[plevel]; scount++) {
          arduboy.drawPixel(this->_stars[si].x, this->_stars[si].y, WHITE);
          this->_stars[si].x -= this->_parallax_rates[plevel];
          if (this->_stars[si].x < 0) {
            this->_stars[si].x = WIDTH - 1;
            this->_stars[si].y = random(HEIGHT - 1);
          }
          si++;
        }
      }
    }
};

#endif // STARFIELD_H
