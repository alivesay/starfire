#ifndef SHIP_H
#define SHIP_H

#include "globals.h"
#include "entity.h"
#include "timer.h"
#include "sprite.h"
#include "list.h"

#define SHIP_SHIELD_DELAY 200
#define SHIP_SHIELD_X_OFFSET 9
#define SHIP_SHIELD_Y_OFFSET 4
#define SHIP_SHIELD_RADIUS 9
#define SHIP_FRAME_DELAY 100
#define SHIP_SPRITE_VISIBLE_WIDTH 13
#define SHIP_SPRITE_VISIBLE_HEIGHT 9

class ShipShield : public Entity {
  private:
    Timer _shieldTimer;
    bool _drawShield;

  public:
    ShipShield() : _shieldTimer(SHIP_SHIELD_DELAY), _drawShield(false) {}

    virtual void update() {
      if (this->_shieldTimer.tick()) {
        this->_drawShield = !this->_drawShield;
      }
    }

    virtual void render() {
      if (this->_drawShield) {
        arduboy.drawCircle(
          this->getScreenX() + SHIP_SHIELD_X_OFFSET,
          this->getScreenY() + SHIP_SHIELD_Y_OFFSET,
          SHIP_SHIELD_RADIUS
        );
      }
    }
};

class BulletEmitter : public Entity {
  List<SPoint*> _bullets;

  virtual void update() {
    if (arduboy.pressed(B_BUTTON)) {
      this->_bullets.pushFront(new SPoint(20, 20));
    }
  }
  virtual void render() {
  }
};

class Ship : public Entity {
  private:
    Sprite _sprite;
    ShipShield _shipShield;

  public:
    Ship() {
      this->setPosition(10, 30);
      this->_sprite.setBitmap(ship_bitmap, ship_mask, 3);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);

      this->addChild(&this->_shipShield);
      this->addChild(&this->_sprite);
    }

    virtual void update() {
      if(arduboy.pressed(LEFT_BUTTON)) {
        this->setX(max(this->getX() - 1, 0));
      }
      if(arduboy.pressed(RIGHT_BUTTON)) {
          this->setX(min(this->getX() + 1, WIDTH - SHIP_SPRITE_VISIBLE_WIDTH));
      }
      if(arduboy.pressed(UP_BUTTON)) {
          this->setY(max(this->getY() - 1, 0));
      }
      if(arduboy.pressed(DOWN_BUTTON)) {
          this->setY(min(this->getY() + 1, HEIGHT - SHIP_SPRITE_VISIBLE_HEIGHT));
      }

      this->updateChildren();
    }

    virtual void render() {
      this->_sprite.render();
      this->renderChildren();
    }
};

#endif // SHIP_H
