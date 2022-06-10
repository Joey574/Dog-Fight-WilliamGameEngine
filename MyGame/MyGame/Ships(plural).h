#pragma once

#include "Engine//GameEngine.h"

class Ships : public GameObject
{
public:

	Ships(int x);

	void draw();
	void update(sf::Time& elapsed);

	void shipMove(int msElapsed);

	sf::FloatRect getCollisionRect();

	void edgeCheck(float x, float y);
	void rotationCheck(float& tempW, float& tempH, int rotation);
	void rotationSet(bool up, bool down, bool left, bool right);

	void handleCollision(GameObject& otherGameObject);

	void laserShoot(); // weapon type 1
	void shotgunShoot(); // weapon type = 4
	void triLaserShoot(); // weapon type = 3
	void flakShoot(); // weapon type = 2

	void flareShoot();

private:

	sf::Sprite sprite_;

	int ID;

	int rotation;

	int fireTimer_ = 0;

	int flareTimer_ = 0;

	int FIRE_DELAY = 200;

	int weapon_ = 1;

	int ammo_ = 100;

	int flares_ = 3;
};

typedef std::shared_ptr<Ships> ShipsPtr;