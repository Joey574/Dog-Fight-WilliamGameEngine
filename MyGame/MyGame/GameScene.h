#pragma once

#include "Engine/GameEngine.h"

class GameScene : public Scene {
 public:
  // Creates our Scene.
  GameScene();

  int getAmmo1();

  int getAmmo2();

  void decreaseAmmo1(int a);

  void decreaseAmmo2(int a);
private:
	int ammo1_ = 200;
	int ammo2_ = 200;
};

typedef std::shared_ptr<GameScene> GameScenePtr;
