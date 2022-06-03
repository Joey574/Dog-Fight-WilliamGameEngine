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

  void increaseAmmo1();

  void increaseAmmo2();

  int getHealth1();

  int getHealth2();

  void decreaseHealth1(float b);

  void decreaseHealth2(float b);
  
  void increaseHealth1();

  void increaseHealth2();


private:
	int ammo1_ = 100;
	int ammo2_ = 100;
	float health1_ = 10.0;
	float health2_ = 10.0;
};

typedef std::shared_ptr<GameScene> GameScenePtr;
