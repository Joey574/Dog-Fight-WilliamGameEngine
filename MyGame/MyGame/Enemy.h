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

private:
	sf::Sprite sprite_;
	int fireTimer_ = 0;
	int weapon_ = 1;
	int weaptime_ = 10;
};

typedef std::shared_ptr<Enemy> EnemyPtr;