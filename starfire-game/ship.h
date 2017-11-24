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
#define SHIP_BULLET_X_OFFSET 16
#define SHIP_BULLET_Y_OFFSET 3

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
  public:
    BulletEmitter() :
    _bulletSpeed(5),
    _fireDelay(100),
    _bulletTimer(20) {
      this->pos.x = SHIP_BULLET_X_OFFSET;
      this->pos.y = SHIP_BULLET_Y_OFFSET;
    }

    ~BulletEmitter() {
        this->_bullets.destroy();
    }

    virtual void update() {
      if (this->_fireDelay.tick() && arduboy.pressed(B_BUTTON)) {
        this->_bullets.pushFront(new SPoint(this->getScreenX(), this->getScreenY()));
      }

      if (!(_bulletTimer.tick())) return;

      for (const List<SPoint*>::ListNode* i = this->_bullets.begin();
           i != NULL; i = i->next) {
        i->data->x += this->_bulletSpeed;

        // offscreen?
        if (i->data->x >= WIDTH) {
          this->_bullets.destroy(i);
        }
      }
    }

    virtual void render() {
      for (const List<SPoint*>::ListNode* i = this->_bullets.begin();
           i != NULL; i = i->next) {
        Sprites::drawExternalMask(i->data->x,
                                  i->data->y,
                                  bullet_bitmap,
                                  bullet_mask,
                                  0,
                                  0);
      }
    }

  private:
    List<SPoint*> _bullets;
    uint8_t _bulletSpeed;
    Timer _fireDelay;
    Timer _bulletTimer;
};

class Ship : public Entity {
  private:
    Sprite _sprite;
    ShipShield _shipShield;
    BulletEmitter _bulletEmitter;

  public:
    Ship() {
      this->pos.x = 10;
      this->pos.y = 30;
      this->_sprite.setBitmap(ship_bitmap, ship_mask, 3);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);

      this->_shipShield.setParent(this);
      this->_sprite.setParent(this);
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

      this->_sprite.update();
      this->_shipShield.update();
      this->_bulletEmitter.update();
    }

    virtual void render() {
      this->_sprite.render();
      this->_shipShield.render();
      this->_bulletEmitter.render();
    }
};

#endif // SHIP_H
