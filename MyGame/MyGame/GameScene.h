#pragma once

#include "Engine/GameEngine.h"

class GameScene : public Scene {
 public:
  // Creates our Scene.
  GameScene();

  int getAmmo();

  void decreaseAmmo(int a);
private:
	int ammo_ = 5;
};

typedef std::shared_ptr<GameScene> GameScenePtr;
