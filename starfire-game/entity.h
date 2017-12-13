#ifndef ENTITY_H
#define ENTITY_H

#include "globals.h"

#define ENTITY_FLAG_ISACTIVE 0
#define ENTITY_FLAG_ISHIT 1
#define ENTITY_FLAG_ISDYING 2

class Entity {
  public:
    Point pos;

    Entity() : pos{0,0}, _parent(nullptr), _flags(0) {}

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

    bool isActive() {
      return bitRead(this->_flags, ENTITY_FLAG_ISACTIVE);
    }

    void setActive(bool isActive) {
      bitWrite(this->_flags, ENTITY_FLAG_ISACTIVE, isActive);
    }

    bool isHit() {
      return bitRead(this->_flags, ENTITY_FLAG_ISHIT);
    }

    void setHit(bool isHit) {
      bitWrite(this->_flags, ENTITY_FLAG_ISHIT, isHit);
    }

    bool isDying() {
      return bitRead(this->_flags, ENTITY_FLAG_ISDYING);
    }

    void setDying(bool isDying) {
      bitWrite(this->_flags, ENTITY_FLAG_ISDYING, isDying);
    }

    void setFlags(uint8_t flags) {
      this->_flags = flags;
    }

    void setCurrentFrame(uint8_t frame) {
      this->_flags = (this->_flags & 0b00001111) | (frame << 4);
    }

    uint8_t getCurrentFrame() {
      return this->_flags >> 4;
    }

    void advanceFrame() {
      this->setCurrentFrame(this->getCurrentFrame() + 1);
    }

    private:
      Entity* _parent;
      uint8_t _flags;
};

#endif // ENTITY_H
