#pragma once

#include "Engine//GameEngine.h"

#include "GameScene.h"
#include "Explosion.h"

class Missile : public GameObject
{
public:
	Missile(sf::Vector2f pos, int rot, int ID);

	void setID(int ID);

	void draw();
	void update(sf::Time& elapsed);

	sf::FloatRect getCollisionRect();

	void handleCollision(GameObject& otherGameObject);

	void rotationSet(sf::Vector2f pos, sf::Vector2f Target);

private:
	sf::Sprite sprite_;
	
	float SPEED;

	int ID_;

	int rotation;

	int forwardTime = 200;

	sf::FloatRect tBounds;
};

typedef std::shared_ptr<Missile> MissilePtr;