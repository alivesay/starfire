#include "globals.h"
#include "starfield.h"
#include "ship.h"
#include "statusbar.h"
#include "entity.h"
#include "stages.h"
#include "collide.h"

Starfield starfield;
Ship ship;
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
    Collide::checkPlayerHit();
    Collide::checkEnemyHit();
    starfield.update();
    Stages::update();
    ship.update();
    statusBar.update();

    starfield.render();
    Stages::render();
    ship.render();
    statusBar.render();
  }

  arduboy.display();
}
