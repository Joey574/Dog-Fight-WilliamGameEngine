#pragma once

#include "Engine//GameEngine.h"

#include "GameScene.h"
#include "Explosion.h"

class Flares : public GameObject
{
public:
	Flares(sf::Vector2f pos, int rot);

	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);

private:
	sf::Sprite sprite_;
};

typedef std::shared_ptr<Flares> FlaresPtr;
