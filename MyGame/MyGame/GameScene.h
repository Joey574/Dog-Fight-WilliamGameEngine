#pragma once

#include "Engine/GameEngine.h"

class GameScene : public Scene {
 public:
  // Creates our Scene.
  GameScene(int player_);

  void players(int player_);

  void setAmmo1(int a);
  
  void setAmmo2(int a);

  float getHealth1();

  float getHealth2();

  void decreaseHealth1(float b);

  void decreaseHealth2(float b);
  
  void increaseHealth1();

  void increaseHealth2();

  void setShipPos(sf::Vector2f ship);

  void setEnemyPos(sf::Vector2f enemy);

  sf::Vector2f getShipPos();

  sf::Vector2f getEnemyPos();

private:
	int player;

	int ammo1_ = 100;
	int ammo2_ = 100;

	float health1_ = 10.0f;
	float health2_ = 10.0f;

	sf::Vector2f shipPos;
	sf::Vector2f enemyPos;

};

typedef std::shared_ptr<GameScene> GameScenePtr;
