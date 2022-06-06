#pragma once

#include "Engine//GameEngine.h"

class Enemy : public GameObject
{
public:

	Enemy();

	void draw();
	void update(sf::Time& elapsed);

	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);

	void edgeCheck(float x, float y);
	void rotationCheck(float& tempW, float& tempH, int rotation);
	void rotationSet(bool up, bool down, bool left, bool right);

	int laserShoot(int ammo); // weapon type 1
	int shotgunShoot(int ammo); // weapon type = 4
	int triLaserShoot(int ammo); // weapon type = 3
	int flakShoot(int ammo); // weapon type = 2

private:
	sf::Sprite sprite_;

	int rotation;

	int fireTimer_ = 0;
	int FIRE_DELAY = 200;
	int weapon_ = 1;
};

typedef std::shared_ptr<Enemy> EnemyPtr;