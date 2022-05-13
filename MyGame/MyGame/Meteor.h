#pragma once
#include "Engine/GameEngine.h"

#include "Explosion.h"

class Meteor : public GameObject
{
public:
	// Creates our Meteor.
	Meteor(sf::Vector2f pos, float speedV);
	// Functions overridden from GameObject:
	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();
	void handleCollision(GameObject& otherGameObject);
private:
	sf::Sprite sprite_;
	float speedVa;
};
typedef std::shared_ptr<Meteor> MeteorPtr;