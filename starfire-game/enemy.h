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
};

const EnemyData enemyData[3] = {
  // mark 0
  {
    bitmap: mark0_plus_mask,
    width: 18,
    height: 16,
    frameCount: 2,
    frameDelay: 40,
    speed: 1
  },
  // mark 1
  {
    bitmap: mark1_plus_mask,
    width: 31,
    height: 28,
    frameCount: 2,
    frameDelay: 40,
    speed: 1
  },
  // mark 3
  {
    bitmap: mark3_plus_mask,
    width: 12,
    height: 9,
    frameCount: 2,
    frameDelay: 40,
    speed: 2
  },
};

enum EnemyState {
  Idle,
  FlyingIn,
  FlyingUp,
  FlyingDown
};

class Enemy : public Entity {
  public:
    Enemy() : _state(EnemyState::Idle) {
      this->_sprite.setParent(this);
    }

    void render() {
      this->_sprite.render();
    }

    void setType(uint8_t type) {
      this->_sprite.setBitmap(enemyData[type].bitmap, enemyData[type].frameCount);
      this->_sprite.autoPlay(enemyData[type].frameDelay);
      this->_type = type;
    }

    uint8_t getType() {
      return this->_type;
    }

    uint8_t getSpeed() {
      return enemyData[this->_type].speed;
    }

    EnemyState getState() {
      return this->_state;
    }

    void setState(EnemyState state) {
      this->_state = state;
    }

    uint8_t getWidth() {
      return enemyData[this->_type].width;
    }

    uint8_t getHeight() {
      return enemyData[this->_type].height;
    }

  private:
    Sprite _sprite;
    uint8_t _type;
    EnemyState _state;
};

#endif // ENEMY_H
