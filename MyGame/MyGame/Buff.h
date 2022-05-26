#pragma once

#include "Engine//GameEngine.h"

#include "GameScene.h"

class Buff : public GameObject
{
public:
	Buff();

	void draw();
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);

private:
	sf::Sprite sprite_;
	int type;
};

typedef std::shared_ptr<Buff> BuffPtr;
