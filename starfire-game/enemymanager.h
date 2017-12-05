#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "globals.h"
#include "enemy.h"

Enemy enemies[ENEMY_MAX_COUNT];

class EnemyManager {
  public:
    static void update() {
      // detect collision
      // enemy takes damage on hit
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
        if (enemies[i].isActive() && enemies[i].pos.x <= -pgm_read_byte(&enemyData[enemies[i].getType()].bitmap[0])) {
          enemies[i].setActive(false);
        }
      }

    }

    static void render() {
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
        if (enemies[i].isActive()) enemies[i].render();
      }
    }

    static void spawnRandom(uint8_t type, uint8_t start, uint8_t end, uint8_t spacingX) {
      for (uint8_t i = start; i < end; i++) {
        enemies[i].pos.x = WIDTH + (spacingX * (i - start));
        enemies[i].pos.y = random(10, 32);
        enemies[i].setType(type);
        enemies[i].setActive(true);
      }
    }

    static void flySineRightLeft(uint8_t start, uint8_t end) {
      for (uint8_t i = start; i < end; i++) {
        enemies[i].pos.x -= enemies[i].getSpeed();
        //enemies[i].pos.y = sin(arduboy.frameCount * 0.05) * 16 + 24;
        enemies[i].pos.y = sin(enemies[i].pos.x * 0.05) * 16 + 24;
      }
    }

    static void flyRightLeft(uint8_t start, uint8_t end) {
      for (uint8_t i = start; i < end; i++) {
        enemies[i].pos.x -= enemies[i].getSpeed();
      }
    }

    static void flyUpDown(uint8_t start, uint8_t end, uint8_t x) {
      for (uint8_t i = start; i < end; i++) {
        // fly in from the right
        if (enemies[i].pos.x > x) {
          enemies[i].setState(EnemyMoveState::FlyingIn);
        } else {
          // initial direction
          if (enemies[i].getState() == EnemyMoveState::FlyingIn) {
            enemies[i].setState(EnemyMoveState::FlyingUp);
          }
          // fly up and down
          if (enemies[i].pos.y < 4) {
            enemies[i].setState(EnemyMoveState::FlyingDown);
          } else if (enemies[i].pos.y > (HEIGHT - enemies[i].getHeight() - 4)) {
            enemies[i].setState(EnemyMoveState::FlyingUp);
          }
        }

        switch (enemies[i].getState()) {
          case EnemyMoveState::FlyingIn:
            enemies[i].pos.x -= enemies[i].getSpeed();
            break;
          case EnemyMoveState::FlyingDown:
            enemies[i].pos.y += enemies[i].getSpeed();
            break;
          case EnemyMoveState::FlyingUp:
            enemies[i].pos.y -= enemies[i].getSpeed();
            break;
        }
      }
    }
};

#endif // ENEMYMANAGER_H
