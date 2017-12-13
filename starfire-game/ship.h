#ifndef SHIP_H
#define SHIP_H

#include "globals.h"
#include "entity.h"
#include "timer.h"
#include "sprite.h"
#include "enemy.h"

#define SHIP_SHIELD_DELAY 200
#define SHIP_SHIELD_X_OFFSET 9
#define SHIP_SHIELD_Y_OFFSET 4
#define SHIP_SHIELD_RADIUS 9
#define SHIP_FRAME_DELAY 40
#define SHIP_SPRITE_VISIBLE_WIDTH 13
#define SHIP_SPRITE_VISIBLE_HEIGHT 9
#define SHIP_BULLET_WIDTH 4
#define SHIP_BULLET_HEIGHT 3
#define SHIP_BULLET_X_OFFSET 16
#define SHIP_BULLET_Y_OFFSET 3
#define SHIP_MAX_BULLET_COUNT 7
#define SHIP_LASER_X_OFFSET 16
#define SHIP_LASER_Y_OFFSET -20
#define SHIP_LASER_DELAY 40

#define SHIP_FLAG_LASERFIRING 0

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

class Bullet : public Entity {
  public:
    virtual void render() {
      Sprites::drawPlusMask(this->pos.x,
                            this->pos.y,
                            bullet_plus_mask,
                            0);
    }
};

Bullet bullets[SHIP_MAX_BULLET_COUNT];

class BulletEmitter : public Entity {
  public:
    BulletEmitter() :
    _bulletSpeed(5),
    _fireDelay(100),
    _bulletTimer(20)
    {
      this->pos.x = SHIP_BULLET_X_OFFSET;
      this->pos.y = SHIP_BULLET_Y_OFFSET;
    }

    uint8_t getBulletCount() {
      uint8_t count = 0;
      for (uint8_t i = 0; i < SHIP_MAX_BULLET_COUNT; i++) {
        if (bullets[i].isActive()) count++;
      }

      return count;
    }

    virtual void update() {
      if (this->_fireDelay.tick() && arduboy.pressed(B_BUTTON) && this->getBulletCount() < SHIP_MAX_BULLET_COUNT) {

        Bullet* bullet = this->_getFreeBullet();
        if (bullet != nullptr) {
          bullet->pos.x = this->getScreenX();
          bullet->pos.y = this->getScreenY();
          bullet->setActive(true);
        }
      }

      if (!(this->_bulletTimer.tick())) return;

      for (uint8_t i = 0; i < SHIP_MAX_BULLET_COUNT; i++) {
        if (bullets[i].isActive()) {
          bullets[i].pos.x += this->_bulletSpeed;
          // is offscreen
          if (bullets[i].pos.x >= WIDTH) {
            bullets[i].setActive(false);
          }
        }
      }
    }

    virtual void render() {
      for (uint8_t i = 0; i < SHIP_MAX_BULLET_COUNT; i++) {
        if (bullets[i].isActive()) bullets[i].render();
      }
    }

  private:
    uint8_t _bulletSpeed;
    Timer _fireDelay;
    Timer _bulletTimer;

    Bullet* _getFreeBullet() {
      for (uint8_t i = 0; i < SHIP_MAX_BULLET_COUNT; i++) {
        if (!(bullets[i].isActive())) return &bullets[i];
      }

      return nullptr;
    }
};

class Ship : public Entity {
  private:
    Sprite _sprite;
    Sprite _laserSprite;
    ShipShield _shipShield;
    BulletEmitter _bulletEmitter;
    uint8_t _flags;

  public:
    uint8_t health;

    Ship() :
    _flags(false) {
      this->pos.x = 10;
      this->pos.y = 30;

      this->_sprite.setBitmap(ship_plus_mask, 4);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);

      this->_laserSprite.pos.x = SHIP_LASER_X_OFFSET;
      this->_laserSprite.pos.y = SHIP_LASER_Y_OFFSET;
      this->_laserSprite.setBitmap(laser_plus_mask, 2);
      this->_laserSprite.autoPlay(SHIP_LASER_DELAY);

      this->_shipShield.setParent(this);
      this->_sprite.setParent(this);
      this->_laserSprite.setParent(this);
      this->_bulletEmitter.setParent(this);
    }

    virtual void update() {
      if(arduboy.pressed(LEFT_BUTTON)) {
        this->pos.x = max(this->pos.x - 1, 0);
      }
      if(arduboy.pressed(RIGHT_BUTTON)) {
          this->pos.x = min(this->pos.x + 1, WIDTH - SHIP_SPRITE_VISIBLE_WIDTH);
      }
      if(arduboy.pressed(UP_BUTTON)) {
          this->pos.y = max(this->pos.y - 1, 0);
      }
      if(arduboy.pressed(DOWN_BUTTON)) {
          this->pos.y = min(this->pos.y + 1, HEIGHT - SHIP_SPRITE_VISIBLE_HEIGHT);
      }

      this->setLaserFiring(arduboy.pressed(A_BUTTON));
      if (this->isLaserFiring()) this->_laserSprite.update();
      this->_sprite.update();
      this->_shipShield.update();
      this->_bulletEmitter.update();
    }

    virtual void render() {
      if (this->isLaserFiring()) this->_laserSprite.render();
      this->_sprite.render();
      this->_shipShield.render();
      this->_bulletEmitter.render();
    }

    bool isLaserFiring() {
      return bitRead(this->_flags, SHIP_FLAG_LASERFIRING);
    }

    void setLaserFiring(bool isFiring) {
      bitWrite(this->_flags, SHIP_FLAG_LASERFIRING, isFiring);
    }
};

Ship ship;

#endif // SHIP_H
