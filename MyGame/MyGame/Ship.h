#pragma once

#include "Engine//GameEngine.h"

class Ship : public GameObject
{
public:

	Ship();

	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	sf::Vector2f shipPos();

	void edgeCheck(float x, float y);
	void rotationCheck(float& tempW, float& tempH, int rotation);
	void rotationSet(bool up, bool down, bool left, bool right);

private:
	sf::Sprite sprite_;
	int fireTimer_ = 0;
};

typedef std::shared_ptr<Ship> ShipPtr;