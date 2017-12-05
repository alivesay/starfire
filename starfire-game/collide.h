#ifndef COLLIDE_H
#define COLLIDE_H

#include "globals.h"
#include "ship.h"
#include "enemy.h"

class Collide {
  public:
    static void checkPlayerHit() {
      // does ship collide with an enemy?
      // does ship collide with an enemy bullet?
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {

      }
    }

    static void checkEnemyHit() {
      // does player bullet collide with an enemy?
      // does player lazer collide with an enemy?
      Rect enemyRect;
      Rect bulletRect;
      bool isCollision;

      bulletRect.width = SHIP_BULLET_WIDTH;
      bulletRect.height = SHIP_BULLET_HEIGHT;

      for (uint8_t i = 0; i < SHIP_MAX_BULLET_COUNT; i++) {
        if (bullets[i].isActive()) {
          bulletRect.x = bullets[i].pos.x;
          bulletRect.y = bullets[i].pos.y;

          for (uint8_t j = 0; j < ENEMY_MAX_COUNT; j++) {
            if (enemies[j].isActive()) {
              switch (enemies[j].getType()) {
                case ENEMY_MARK_0:
                  enemyRect.x = enemies[j].pos.x;
                  enemyRect.y = enemies[j].pos.y;
                  enemyRect.width = 12;
                  enemyRect.height = 13;
                  isCollision = arduboy.collide(bulletRect, enemyRect);
                  break;
                case ENEMY_MARK_1:
                  enemyRect.x = enemies[j].pos.x + 3;
                  enemyRect.y = enemies[j].pos.y + 5;
                  enemyRect.width = 19;
                  enemyRect.height = 21;
                  isCollision = arduboy.collide(bulletRect, enemyRect);
                  enemyRect.x = enemies[j].pos.x + 10;
                  enemyRect.y = enemies[j].pos.y;
                  enemyRect.width = 12;
                  enemyRect.height = 5;
                  isCollision |= arduboy.collide(bulletRect, enemyRect);
                  break;
                case ENEMY_MARK_3:
                  enemyRect.x = enemies[j].pos.x + 1;
                  enemyRect.y = enemies[j].pos.y + 1;
                  enemyRect.width = 7;
                  enemyRect.height = 7;
                  isCollision = arduboy.collide(bulletRect, enemyRect);
                  break;
              }

              if (isCollision) {
                bullets[i].setActive(false);
                if (enemies[j].hit(1)) enemies[j].setActive(false);
                isCollision = false;
              }
            }
          }
        }
      }
    }
};

#endif // COLLIDE_H
