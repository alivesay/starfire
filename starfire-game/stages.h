#ifndef STAGES_H
#define STAGES_H

#include "globals.h"
#include "enemy.h"
#include "enemymanager.h"

extern const FuncPtr stageData[1][3];

class Stages {
  public:
    static uint8_t currentStage;
    static uint8_t currentWave;
    static uint8_t previousWave;
    static EnemyManager enemyManager;

    static void update() {
      if (arduboy.everyXFrames(2)) {
        Stages::enemyManager.update();
        Stages::runWave();
      }
    }

    static void render() {
      Stages::enemyManager.render();
    }

    static void runWave() {
        ((FuncPtr)pgm_read_word(&stageData[Stages::currentStage][Stages::currentWave]))();
    }

    static bool checkWaveStart() {
      if (Stages::previousWave != Stages::currentWave) {
        Stages::previousWave = Stages::currentWave;
        return true;
      }
      return false;
    }

    static bool checkWaveEnd() {
      uint8_t numActive = 0;
      for (uint8_t i = 0; i < ENEMY_MAX_COUNT; i++) {
        if (enemies[i].isActive()) numActive++;
      }

      if (numActive == 0) Stages::currentWave++;

      // TODO:
      if (Stages::currentWave == 3) {
        Stages::currentWave = 0;
        Stages::previousWave = 255;
      }

      return numActive == 0;
    }

    static void wave000() {
      //wait();
      if (Stages::checkWaveStart()) {
        EnemyManager::spawnRandom(ENEMY_MARK_0, 0, 3, 20);
        EnemyManager::spawnRandom(ENEMY_MARK_3, 3, ENEMY_MAX_COUNT, 20);
      }
      EnemyManager::flySineRightLeft(0, 3, 0);
      EnemyManager::flyRightLeft(3, ENEMY_MAX_COUNT);
      Stages::checkWaveEnd();
    }

    static void wave001() {
      if (Stages::checkWaveStart()) {
        EnemyManager::spawnRandom(ENEMY_MARK_1, 0, 2, 20);
      }
      EnemyManager::flyUpDown(0, 1, 97);
      EnemyManager::flyUpDown(1, 2, 62);
      Stages::checkWaveEnd();
    }

    static void wave002() {
      if (Stages::checkWaveStart()) {
        EnemyManager::spawnRandom(ENEMY_MARK_3, 0, 5, 20);
        EnemyManager::spawnRandom(ENEMY_MARK_3, 5, ENEMY_MAX_COUNT, 20);
      }
      EnemyManager::flySineRightLeft(0, 5, 0);
      EnemyManager::flySineRightLeft(5, ENEMY_MAX_COUNT, 24);
      Stages::checkWaveEnd();
    }
};

uint8_t Stages::currentStage = 0;
uint8_t Stages::currentWave = 0;
uint8_t Stages::previousWave = 255;

const FuncPtr PROGMEM stageData[1][3] = {
  {
    Stages::wave000,
    Stages::wave001,
    Stages::wave002
  }
};

#endif // STAGES_H
