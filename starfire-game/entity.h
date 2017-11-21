#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"
#include "list.h"
#include "position.h"

class IUpdateable {
  public:
    virtual void update() = 0;
};

class IRenderable {
  public:
    virtual void render() = 0;
};

class IEntity : public IUpdateable,
                public IRenderable,
                public IPositionable {
  public:
    virtual void setParent(IEntity* parent) = 0;
    virtual void addChild(IEntity* child) = 0;
    virtual void updateChildren() = 0;
    virtual void renderChildren() = 0;
    virtual const int16_t getScreenX() = 0;
    virtual const int16_t getScreenY() = 0;
};

class Entity : public IEntity {
  protected:
    Point _pos;

  public:
    virtual Entity() : _pos{0,0}, _parent(NULL) {}

    virtual ~Entity() {
      this->_children.clear();
    }

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

    void setParent(IEntity* parent) {
      this->_parent = parent;
    }

    void addChild(IEntity* child) {
      child->setParent(this);
      this->_children.pushFront(child);
    }

    void updateChildren() {
      for (const List<IEntity*>::ListNode* i = this->_children.begin();
           i != NULL; i = i->next) {
        i->data->update();
      }
    }

    void renderChildren() {
      for (const List<IEntity*>::ListNode* i = this->_children.begin();
           i != NULL; i = i->next) {
        i->data->render();
      }
    }

    virtual void update() {
      this->updateChildren();
    }

    virtual void render() {
      this->renderChildren();
    }

    const int16_t getScreenX() {
      return (this->_parent) ? this->_parent->getX() + this->getX() : this->getX();
    }

    const int16_t getScreenY() {
      return (this->_parent) ? this->_parent->getY() + this->getY() : this->getY();
    }

    private:
      IEntity* _parent;
      List<IEntity*> _children;
};

#endif // ENTITY_H
