#ifndef POSITION_H
#define POSITION_H

class IPositionable {
  public:
    virtual void setPosition(Point point) = 0;
    virtual void setPosition(int16_t x, int16_t y) = 0;
    virtual Point getPosition() = 0;
    virtual const int16_t getX() = 0;
    virtual const int16_t getY() = 0;
    virtual void setX(const int16_t x) = 0;
    virtual void setY(const int16_t y) = 0;
};

#endif // POSITION_H
