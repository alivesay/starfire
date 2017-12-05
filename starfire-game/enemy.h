#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "timer.h"

#define ENEMY_MAX_COUNT 5
#define ENEMY_FRAME_DELAY 40

#define ENEMY_MARK_0 0
#define ENEMY_MARK_1 1
#define ENEMY_MARK_3 2

struct EnemyData {
    uint8_t* bitmap;
    uint8_t width;
    uint8_t height;
    uint8_t frameCount;
    uint8_t frameDelay;
    uint8_t speed;
    uint8_t health;
};

const EnemyData enemyData[3] = {
  // mark 0
  {
    bitmap: mark0_plus_mask,
    width: 18,
    height: 16,
    frameCount: 2,
    frameDelay: 40,
    speed: 1,
    health: 5
  },
  // mark 1
  {
    bitmap: mark1_plus_mask,
    width: 31,
    height: 28,
    frameCount: 2,
    frameDelay: 40,
    speed: 1,
    health: 20
  },
  // mark 3
  {
    bitmap: mark3_plus_mask,
    width: 12,
    height: 9,
    frameCount: 2,
    frameDelay: 40,
    speed: 2,
    health: 2
  },
};

enum EnemyMoveState {
  Idle,
  FlyingIn,
  FlyingUp,
  FlyingDown
};

class Enemy : public Entity {
  public:
    uint8_t health;

    Enemy() : _state(EnemyMoveState::Idle) {
      this->_sprite.setParent(this);
    }

    void render() {
      if (this->isHit()) {
        this->setHit(false);
        return;
      }

      this->_sprite.render();
    }

    void setType(uint8_t type) {
      this->_sprite.setBitmap(enemyData[type].bitmap, enemyData[type].frameCount);
      this->_sprite.autoPlay(enemyData[type].frameDelay);
      this->_type = type;
      this->health = enemyData[type].health;
    }

    uint8_t getType() {
      return this->_type;
    }

    uint8_t getSpeed() {
      return enemyData[this->_type].speed;
    }

    EnemyMoveState getState() {
      return this->_state;
    }

    void setState(EnemyMoveState state) {
      this->_state = state;
    }

    uint8_t getWidth() {
      return enemyData[this->_type].width;
    }

    uint8_t getHeight() {
      return enemyData[this->_type].height;
    }

    bool hit(uint8_t damage) {
      this->setHit(true);
      this->health -= damage;

      return this->health == 0;
    }

  private:
    Sprite _sprite;
    uint8_t _type;
    EnemyMoveState _state;
};

#endif // ENEMY_H
