#include "globals.h"
#include "starfield.h"
#include "ship.h"
#include "statusbar.h"
#include "entity.h"

Entity scene;
Starfield starfield;
Ship ship;
StatusBar statusBar;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);

  scene.addChild(&statusBar);
  scene.addChild(&ship);
  scene.addChild(&starfield);
}

void loop() {
  if(!(arduboy.nextFrame())) return;

  arduboy.clear();

  scene.updateChildren();
  scene.renderChildren();

  if(arduboy.pressed(A_BUTTON)) {
    arduboy.fillRoundRect(1, 31, 126, 32, 1, WHITE);
    arduboy.setCursor(10, 40);
    arduboy.setTextColor(BLACK);
    arduboy.setTextBackground(WHITE);
    arduboy.print("Example Text");
  }

  arduboy.display();
}
