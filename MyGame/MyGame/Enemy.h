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

private:
	sf::Sprite sprite_;
	int fireTimer_ = 0;
	int weapon_ = 1;
	int weaptime_ = 10;
};

typedef std::shared_ptr<Enemy> EnemyPtr;