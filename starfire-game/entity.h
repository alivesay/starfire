#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"
#include "list.h"
#include "position.h"

class Entity {
  public:
    Point pos;

    Entity() : pos{0,0}, _parent(NULL) {}

    ~Entity() {
      this->_children.clear();
    }

    void setParent(Entity* parent) {
      this->_parent = parent;
    }

    void addChild(Entity* child) {
      child->setParent(this);
      this->_children.pushFront(child);
    }

    void updateChildren() {
      for (const List<Entity*>::ListNode* i = this->_children.begin();
           i != NULL; i = i->next) {
        i->data->update();
      }
    }

    void renderChildren() {
      for (const List<Entity*>::ListNode* i = this->_children.begin();
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
      return (this->_parent) ? this->_parent->pos.x + this->pos.x : this->pos.x;
    }

    const int16_t getScreenY() {
      return (this->_parent) ? this->_parent->pos.y + this->pos.y : this->pos.y;
    }

    private:
      Entity* _parent;
      List<Entity*> _children;
};

#endif // ENTITY_H
