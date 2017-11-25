#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "timer.h"

#define ENEMY_MAX_COUNT 5

class Enemy : public Entity {
  public:
    Enemy() {
      this->_sprite.setBitmap(enemy_bitmap, enemy_mask, 2);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);

      this->_sprite.setParent(this);
    }

    void render() {
      this->_sprite.render();
    }

  private:
    Sprite _sprite;
};

class EnemyEmitter : public Entity {
  public:
    EnemyEmitter() :
    _spawnTimer(1000),
    _frameTimer(20) {}

    void update() {
      if (this->_spawnTimer.tick() && this->_enemyCount < ENEMY_MAX_COUNT) {
        Enemy* enemy = this->_getFreeEnemy();
        if (enemy != nullptr) {
          enemy->pos.x = 128;
          enemy->pos.y = random(10, 50);
          enemy->setActive(true);
          this->_enemyCount++;
        }
      }

      if (!(this->_frameTimer.tick())) return;

      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
        if (this->_enemies[i].isActive()) {
          this->_enemies[i].pos.x--;
          if (this->_enemies[i].pos.x <= -26) {
            this->_enemies[i].setActive(false);
            this->_enemyCount--;
          }
        }
      }
    }

    void render() {
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
        if (this->_enemies[i].isActive()) this->_enemies[i].render();
      }
    }

  private:
    Timer _spawnTimer;
    Timer _frameTimer;
    uint8_t _enemyCount;
    Enemy _enemies[ENEMY_MAX_COUNT];

    Enemy* _getFreeEnemy() {
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
        if (!(this->_enemies[i].isActive())) return &this->_enemies[i];
      }

      return nullptr;
    }
};

#endif // ENEMY_H
