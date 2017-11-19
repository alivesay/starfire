#include "globals.h"
#include "entity.h"
#include "starfield.h"
#include "ship.h"

Point ship_loc;
Point bullet_loc;
Starfield starfield;
Ship ship;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  if(!(arduboy.nextFrame())) return;

  arduboy.clear();

  starfield.render();
  ship.update();
  ship.render();

  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  arduboy.print("cpu: ");
  arduboy.print(arduboy.cpuLoad());

  if(arduboy.pressed(A_BUTTON)) {
    arduboy.fillRoundRect(1, 31, 126, 32, 1, WHITE);
    arduboy.setCursor(10, 40);
    arduboy.setTextColor(BLACK);
    arduboy.setTextBackground(WHITE);
    arduboy.print("Example Text");
  }

  arduboy.display();
}
