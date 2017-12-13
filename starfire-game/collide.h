#ifndef COLLIDE_H
#define COLLIDE_H

#include "globals.h"
#include "ship.h"
#include "enemy.h"

class Collide {
  public:
    static void checkPlayerHit() {
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
      }
    }

    static void checkEnemyHit() {
      Rect bulletRect;
      Rect laserRect;

      bulletRect.width = SHIP_BULLET_WIDTH;
      bulletRect.height = SHIP_BULLET_HEIGHT;
      laserRect.x = ship.pos.x + 16;
      laserRect.y = ship.pos.y - 8;
      laserRect.width = 128;
      laserRect.height = 24;

      // check bullets
      for (uint8_t i = 0; i < SHIP_MAX_BULLET_COUNT; i++) {
        if (bullets[i].isActive()) {
          bulletRect.x = bullets[i].pos.x;
          bulletRect.y = bullets[i].pos.y;

          for (uint8_t j = 0; j < ENEMY_MAX_COUNT; j++) {
            if (enemies[j].isActive() && !enemies[j].isDying()) {
              if (Collide::_collidesEnemy(&enemies[j], &bulletRect)) {
                bullets[i].setActive(false);
                enemies[j].hit(1);
              }
            }
          }
        }
      }

      // check laser
      if (ship.isLaserFiring()) {
        for (uint8_t j = 0; j < ENEMY_MAX_COUNT; j++) {
          if (enemies[j].isActive() && !enemies[j].isDying()) {
            if (Collide::_collidesEnemy(&enemies[j], &laserRect)) {
              enemies[j].hit(1);
            }
          }
        }
      }
    }

  private:
    static bool _collidesEnemy(Enemy* enemy, Rect* bulletRect) {
      Rect enemyRect;
      bool isCollision;

      switch (enemy->getType()) {
        case ENEMY_MARK_0:
          enemyRect.x = enemy->pos.x;
          enemyRect.y = enemy->pos.y;
          enemyRect.width = 12;
          enemyRect.height = 13;
          isCollision = arduboy.collide(*bulletRect, enemyRect);
          break;
        case ENEMY_MARK_1:
          enemyRect.x = enemy->pos.x + 3;
          enemyRect.y = enemy->pos.y + 5;
          enemyRect.width = 19;
          enemyRect.height = 21;
          isCollision = arduboy.collide(*bulletRect, enemyRect);
          enemyRect.x = enemy->pos.x + 10;
          enemyRect.y = enemy->pos.y;
          enemyRect.width = 12;
          enemyRect.height = 5;
          isCollision |= arduboy.collide(*bulletRect, enemyRect);
          break;
        case ENEMY_MARK_3:
          enemyRect.x = enemy->pos.x + 1;
          enemyRect.y = enemy->pos.y + 1;
          enemyRect.width = 7;
          enemyRect.height = 7;
          isCollision = arduboy.collide(*bulletRect, enemyRect);
          break;
      }

      return isCollision;
    }
};

#endif // COLLIDE_H
