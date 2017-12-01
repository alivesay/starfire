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
    uint8_t frameCount;
    uint8_t frameDelay;
};

const EnemyData enemyData[3] = {
  // mark 0
  {
    bitmap: mark0_plus_mask,
    frameCount: 2,
    frameDelay: 40
  },
  // mark 1
  {
    bitmap: mark1_plus_mask,
    frameCount: 2,
    frameDelay: 40
  },
  // mark 3
  {
    bitmap: mark3_plus_mask,
    frameCount: 2,
    frameDelay: 40
  },
};

class Enemy : public Entity {
  public:
    Enemy() {
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

  private:
    Sprite _sprite;
    uint8_t _type;
};

#endif // ENEMY_H
