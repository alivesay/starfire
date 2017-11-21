#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"

class Enemy : public Entity {
  public:
    Enemy() {
      this->pos.x = 100;
      this->pos.y = 24;
      this->_sprite.setBitmap(enemy_bitmap, enemy_mask, 2);
      this->_sprite.autoPlay(SHIP_FRAME_DELAY);

      this->addChild(&this->_sprite);
    }

  private:
    Sprite _sprite;
};

#endif // ENEMY_H
