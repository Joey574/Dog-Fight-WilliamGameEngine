#pragma once

#include "Engine//GameEngine.h"

#include "GameScene.h"
#include "Explosion.h"

class Flare : public GameObject
{
public:
	Flare(sf::Vector2f pos, int rot);

	void draw();
	void update(sf::Time& elapsed);
	void move(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();

private:
	sf::Sprite sprite_;
	int timer_ = 1700;
};

typedef std::shared_ptr<Flare> FlarePtr;