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
	void rotationSet(bool up, bool down, bool left, bool right);

private:
	sf::Sprite sprite_;
	int ID_;
};

typedef std::shared_ptr<Missile> MissilePtr;