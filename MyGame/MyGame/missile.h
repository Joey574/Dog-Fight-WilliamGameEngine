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
	void rotationSet(float x, float y);

private:
	sf::Sprite sprite_;
	
	float SPEED;

	int ID_;

	int rotation;

	int forwardTime = 300;

	sf::FloatRect tBounds;
};

typedef std::shared_ptr<Missile> MissilePtr;