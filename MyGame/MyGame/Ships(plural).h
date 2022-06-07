#pragma once

#include "Engine//GameEngine.h"

class Ships : public GameObject
{
public:

	Ships();

	void draw();
	void update(sf::Time& elapsed);

	void shipMove(int msElapsed);
	void enemyMove(int msElapsed);

	sf::FloatRect getShipCollisionRect();
	sf::Vector2f shipPos();

	sf::FloatRect getEnemyCollisionRect();
	sf::Vector2f enemyPos();

	void edgeCheck(float x, float y, int ID);
	void rotationCheck(float& tempW, float& tempH, int rotation);
	void rotationSet(bool up, bool down, bool left, bool right, int ID);
	void handleCollision(GameObject& otherGameObject, int ID);

	int laserShoot(int ammo, int ID); // weapon type 1
	int shotgunShoot(int ammo, int ID); // weapon type = 4
	int triLaserShoot(int ammo, int ID); // weapon type = 3
	int flakShoot(int ammo, int ID); // weapon type = 2

private:

	sf::Sprite sprite_1;
	sf::Sprite sprite_2;

	int rotation1;
	int rotation2;

	int fireTimer_1 = 0;
	int fireTimer_2 = 0;

	int FIRE_DELAY1 = 200;
	int FIRE_DELAY2 = 200;

	int weapon_1 = 1;
	int weapon_2 = 1;
};

typedef std::shared_ptr<Ships> ShipsPtr;