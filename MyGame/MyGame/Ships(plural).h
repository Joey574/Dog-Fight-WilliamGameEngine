#pragma once

#include "Engine//GameEngine.h"

class Ships : public GameObject
{
public:

	Ships(int ID);

	void draw();
	void update(sf::Time& elapsed);

	void shipMove(int msElapsed);

	sf::FloatRect getCollisionRect();
	sf::Vector2f Pos();

	void edgeCheck(float x, float y, int ID);
	void rotationCheck(float& tempW, float& tempH, int rotation);
	void rotationSet(bool up, bool down, bool left, bool right, int ID);

	void handleCollision(GameObject& otherGameObject);

	int laserShoot(int ammo, int ID); // weapon type 1
	int shotgunShoot(int ammo, int ID); // weapon type = 4
	int triLaserShoot(int ammo, int ID); // weapon type = 3
	int flakShoot(int ammo, int ID); // weapon type = 2

private:

	sf::Sprite sprite_;

	int ID;

	int rotation;

	int fireTimer_ = 0;

	int FIRE_DELAY = 200;

	int weapon_ = 1;
};

typedef std::shared_ptr<Ships> ShipsPtr;