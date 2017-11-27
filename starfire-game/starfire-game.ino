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
Sprite title;

bool atTitle = true;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);

  title.setBitmap(title_plus_mask, 2);
  title.autoPlay(20);
}

void loop() {
  if(!(arduboy.nextFrame())) return;

  arduboy.clear();

  if (atTitle) {
    starfield.update();
    starfield.render();
    title.render();
    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) atTitle = false;
  } else {
  starfield.update();
  enemy.update();
  ship.update();
  statusBar.update();

  starfield.render();
  enemy.render();
  ship.render();
  statusBar.render();
/*
  if(arduboy.pressed(A_BUTTON)) {
    arduboy.fillRoundRect(1, 31, 126, 32, 1, WHITE);
    arduboy.setCursor(10, 40);
    arduboy.setTextColor(BLACK);
    arduboy.setTextBackground(WHITE);
    arduboy.print("Example Text");
  }
*/
}
  arduboy.display();
}
