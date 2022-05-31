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
	void handleCollision(GameObject& otherGameObject);

	void laserShoot(); // weapon type 1
	void shotgunShoot(); // weapon type = 4
	void triLaserShoot(); // weapon type = 3
	void flakShoot(); // weapon type = 2

private:
	sf::Sprite sprite_;

	int rotation;

	int fireTimer_ = 0;
	int shotsf = 2;
	int FIRE_DELAY = 200;
	int weapon_ = 1;
};

typedef std::shared_ptr<Ship> ShipPtr;