#include "Meteor.h"
#include "GameScene.h"

const float SPEED = 0.25f;

Meteor::Meteor(sf::Vector2f pos, float speedV)
{
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	assignTag("meteor");
	speedVa = speedV;
}

void Meteor::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Meteor::update(sf::Time& elapsed) 
{
	int msElapsed = elapsed.asMilliseconds();

	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x < sprite_.getGlobalBounds().width * -1 || pos.y < sprite_.getGlobalBounds().height * -1)
	{
		makeDead();
	}
	else
	{
		sprite_.setPosition(sf::Vector2f(pos.x - ((SPEED + speedVa) * msElapsed), pos.y));
	}
}

sf::FloatRect Meteor::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Meteor::handleCollision(GameObject& otherGameObject)
{
	if (otherGameObject.hasTag("laser"))
	{
		otherGameObject.makeDead();
	}

	sf::Vector2f pos = sprite_.getPosition();

	ExplosionPtr explosion = std::make_shared<Explosion>(sprite_.getPosition());
	GAME.getCurrentScene().addGameObject(explosion);

	

	makeDead();
}