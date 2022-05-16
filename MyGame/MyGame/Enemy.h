#pragma once

#include "Engine//GameEngine.h"

class Ship : public GameObject
{
public:

	Ship();

	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();

private:
	sf::Sprite sprite_;
	int fireTimer_ = 0;
};

typedef std::shared_ptr<Ship> ShipPtr;