#ifndef SPRITE_H
#define SPRITE_H

#include "globals.h"
#include "timer.h"
#include "entity.h"

class Sprite : public Entity {
  private:
    Timer* _frameTimer;
    uint8_t* _bitmap;
    uint8_t _currentFrame;
    uint8_t _frameCount;
    bool _isAutoPlay;

  public:
    Sprite() :
      _frameTimer(NULL),
      _bitmap(NULL),
      _isAutoPlay(false),
      _currentFrame(0)
    {}

    ~Sprite() {
      if (this->_frameTimer) delete this->_frameTimer;
    }

    void setBitmap(uint8_t* bitmap, uint8_t frameCount) {
      this->_bitmap = bitmap;
      this->_frameCount = frameCount;
    }

    void setCurrentFrame(uint8_t frame) {
      this->_currentFrame = frame;
    }

    void setFrameDelay(uint32_t delay) {
      this->_frameTimer->setDelay(delay);
    }

    virtual void update() {}

    virtual void render() {
      if (this->_isAutoPlay && this->_frameTimer->tick()) {
        this->_currentFrame++;
        if (this->_currentFrame >= this->_frameCount) this->_currentFrame = 0;
      }

      Sprites::drawPlusMask(this->getScreenX(),
                            this->getScreenY(),
                            this->_bitmap,
                            this->_currentFrame);
/*
      Sprites::drawExternalMask(this->getScreenX(),
                                this->getScreenY(),
                                this->_bitmap,
                                this->_bitmapMask,
                                this->_currentFrame,
                                this->_currentFrame);
*/
    }

    void autoPlay(uint32_t delay) {
      if (!(this->_frameTimer)) _frameTimer = new Timer(delay);
      this->_isAutoPlay = true;
    }

};

#endif // SPRITE_H
