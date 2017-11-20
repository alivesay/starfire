#ifndef SHIP_H
#define SHIP_H

#include "globals.h"
#include "entity.h"
#include "timer.h"
#include "sprite.h"

#define SHIP_SHIELD_DELAY 200
#define SHIP_FRAME_DELAY 100

class ShipShield : public Entity {
  private:
    Timer* _shieldTimer;
    bool _drawShield;

  public:
    ShipShield() {
      this->_shieldTimer = new Timer(SHIP_SHIELD_DELAY);
      this->_drawShield = false;
    }

    ~ShipShield() {
      delete this->_shieldTimer;
    }

    virtual void update() {
      if (this->_shieldTimer->tick()) {
        this->_drawShield = !this->_drawShield;
      }
    }

    virtual void render() {
      if (this->_drawShield) arduboy.drawCircle(this->getX() + 9, this->getY() + 4, 9);
    }
};

class Ship : public Entity {
  private:
    Sprite _sprite;
    ShipShield _shipShield;

  public:
    Ship() {
      this->_sprite.setBitmap(ship_bitmap, ship_mask, 3);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);
      this->setPosition(10, 30);
    }

    void setPosition(Point point) {
      this->setPosition(point.x, point.y);
    }

    void setPosition(int16_t x, int16_t y) {
      this->setX(x);
      this->setY(y);
      this->_shipShield.setPosition(x, y);
      this->_sprite.setPosition(x, y);
    }

    const int16_t getX() { return this->_pos.x; }
    const int16_t getY() { return this->_pos.y; }

    void setX(int16_t x) {
      this->_pos.x = x;
      this->_shipShield.setX(x);
      this->_sprite.setX(x);
    }

    void setY(int16_t y) {
      this->_pos.y = y;
      this->_shipShield.setY(y);
      this->_sprite.setY(y);
    }

    virtual void update() {
      if(arduboy.pressed(LEFT_BUTTON)) {
        this->setPosition(max(this->getX() - 1, 0), this->getY());
      }
      if(arduboy.pressed(RIGHT_BUTTON)) {
          this->setPosition(min(this->getX() + 1, WIDTH - 13), this->getY());
      }
      if(arduboy.pressed(UP_BUTTON)) {
          this->setPosition(this->getX(), max(this->getY() - 1, 0));
      }
      if(arduboy.pressed(DOWN_BUTTON)) {
          this->setPosition(this->getX(), min(this->getY() + 1, HEIGHT - 9));
      }

      this->_shipShield.update();
    }

    virtual void render() {
      this->_sprite.render();
      this->_shipShield.render();
    }
};

#endif // SHIP_H
