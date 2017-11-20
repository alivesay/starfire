#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"
#include "scene.h"
#include "position.h"

class IUpdateable {
  virtual void update() = 0;
};

class IRenderable {
  virtual void render() = 0;
};

class Entity : public IUpdateable,
               public IRenderable,
               public IPositionable {
  protected:
    Point _pos;

  public:
    virtual void setPosition(Point point) {
      this->setPosition(point.x, point.y);
    }
    virtual void setPosition(int16_t x, int16_t y) {
      this->_pos.x = x;
      this->_pos.y = y;
    }

    virtual Point getPosition() {
      return this->_pos;
    }

    virtual const int16_t getX() { return this->_pos.x; }
    virtual const int16_t getY() { return this->_pos.y; }
    virtual void setX(const int16_t x) { this->_pos.x = x; }
    virtual void setY(const int16_t y) { this->_pos.y = y; }
};

#endif // ENTITY_H
