#include "globals.h"
#include "starfield.h"
#include "ship.h"
#include "statusbar.h"
#include "entity.h"
#include "enemy.h"

Starfield starfield;
Ship ship;
EnemyEmitter enemy;
StatusBar statusBar;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
}

void loop() {
  if(!(arduboy.nextFrame())) return;

  arduboy.clear();

  starfield.update();
  enemy.update();
  ship.update();
  statusBar.update();

  starfield.render();
  enemy.render();
  ship.render();
  statusBar.render();

  if(arduboy.pressed(A_BUTTON)) {
    arduboy.fillRoundRect(1, 31, 126, 32, 1, WHITE);
    arduboy.setCursor(10, 40);
    arduboy.setTextColor(BLACK);
    arduboy.setTextBackground(WHITE);
    arduboy.print("Example Text");
  }

  arduboy.display();
}
