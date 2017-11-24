#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"
#include "list.h"

class Entity {
  public:
    Point pos;

    Entity() : pos{0,0}, _parent(nullptr) {}

    void setParent(Entity* parent) {
      this->_parent = parent;
    }

    virtual void update() {}

    virtual void render() {}

    const int16_t getScreenX() {
      return (this->_parent) ? this->_parent->pos.x + this->pos.x : this->pos.x;
    }

    const int16_t getScreenY() {
      return (this->_parent) ? this->_parent->pos.y + this->pos.y : this->pos.y;
    }

    private:
      Entity* _parent;
};

#endif // ENTITY_H
