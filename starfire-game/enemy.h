#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "timer.h"

class Enemy : public Entity {
  public:
    Enemy(uint8_t x, uint8_t y) {
      this->pos.x = x;
      this->pos.y = y;
      this->_sprite.setBitmap(enemy_bitmap, enemy_mask, 2);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);

      this->_sprite.setParent(this);
    }

  private:
    Sprite _sprite;
};

class EnemyEmitter : public Entity {
  public:
    EnemyEmitter() :
    _spawnTimer(200),
    _frameTimer(20) {}

    void update() {
      /*
      List<Entity*>* enemies = this->getChildren();

      arduboy.setCursor(64,0);
      arduboy.print(enemies->length());

      if (enemies->length() < 40 && this->_spawnTimer.tick()) {
        if (arduboy.pressed(B_BUTTON)) {
        this->addChild(new Enemy(128, random(10,50)));
      }
      }

      if (!(enemies->empty()) && this->_frameTimer.tick()) {
        for (const List<Entity*>::ListNode* i = enemies->begin();
             i != NULL; i = i->next) {
               i->data->pos.x--;
               if (i->data->pos.x == 0) {
                 enemies->destroy(i);
               }
        }
      }
      */
    }

  private:
    Timer _spawnTimer;
    Timer _frameTimer;
    uint8_t _enemyCount;
};

#endif // ENEMY_H
