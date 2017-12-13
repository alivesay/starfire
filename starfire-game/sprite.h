#ifndef SPRITE_H
#define SPRITE_H

#include "globals.h"
#include "timer.h"
#include "entity.h"

#define SPRITE_FLAG_ISAUTOPLAY 0
#define SPRITE_FLAG_ISPLAYONCE 1

class Sprite : public Entity {
  private:
    Timer* _frameTimer;
    uint8_t* _bitmap;
    uint8_t _frameCount;
    uint8_t _flags;

  public:
    Sprite() :
      _frameTimer(NULL),
      _bitmap(NULL),
      _flags(0)
    {}

    ~Sprite() {
      if (this->_frameTimer) delete this->_frameTimer;
    }

    void setBitmap(uint8_t* bitmap, uint8_t frameCount) {
      this->_bitmap = bitmap;
      this->_frameCount = frameCount;
      this->_flags = 0;
      this->setCurrentFrame(0);
    }

    void setFrameDelay(uint32_t delay) {
      this->_frameTimer->setDelay(delay);
    }

    virtual void update() {}

    virtual void render() {
      if (this->isAutoPlay() && this->_frameTimer->tick()) {
        this->advanceFrame();
        if (this->getCurrentFrame() >= this->_frameCount) {
          if (this->isPlayOnce()) {
            return;
          } else {
            this->setCurrentFrame(0);
          }
        }
      }

      Sprites::drawPlusMask(this->getScreenX(),
                            this->getScreenY(),
                            this->_bitmap,
                            this->getCurrentFrame());
    }

    bool isDonePlaying() {
      return this->getCurrentFrame() >= this->_frameCount;
    }

    void autoPlay(uint32_t delay) {
      if (!(this->_frameTimer)) _frameTimer = new Timer(delay);
      this->setAutoPlay(true);
    }

    uint8_t getFrameCount() {
      return this->_frameCount;
    }

    void setAutoPlay(bool isAutoPlay) {
      bitWrite(this->_flags, SPRITE_FLAG_ISAUTOPLAY, isAutoPlay);
    }

    bool isAutoPlay() {
      return bitRead(this->_flags, SPRITE_FLAG_ISAUTOPLAY);
    }

    void setPlayOnce(bool isPlayOnce) {
      bitWrite(this->_flags, SPRITE_FLAG_ISPLAYONCE, isPlayOnce);
    }

    bool isPlayOnce() {
      return bitRead(this->_flags, SPRITE_FLAG_ISPLAYONCE);
    }
};

#endif // SPRITE_H
