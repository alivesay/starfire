#ifndef TIMER_H
#define TIMER_H

class Timer {
  private:
    uint32_t _lastTime;
    uint32_t _delay;

  public:
    Timer(uint32_t delay) : _delay(delay) {}

    // Returns true if delay has been reached.
    bool tick() {
      uint32_t currentTime = millis();

      if ((currentTime - this->_lastTime) > this->_delay) {
        this->_lastTime = currentTime;
        return true;
      }

      return false;
    }

    void setDelay(uint32_t delay) {
      this->_delay = delay;
    }
};

#endif // TIMER_H
