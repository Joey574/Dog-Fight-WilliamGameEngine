#include "Buff.h"

const float SPEED = 1.2f;

Buff::Buff(sf::Vector2f pos)
{
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	type = (rand() % 2) + 1;
	if (type == 1)
	{
		assignTag("health+");
		sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	}
	else if (type == 2)
	{
		assignTag("ammo+");
		sprite_.setTexture(GAME.getTexture("Resources/ship.png"));
	}
}

void Buff::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Buff::update(sf::Time& elapsed)
{
	
}

sf::FloatRect Buff::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Buff::handleCollision(GameObject& otherGameObject)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos = sprite_.getPosition();

	if (otherGameObject.hasTag("ship"))
	{
		if (hasTag("health+"))
		{
			scene.increaseHealth1();
		}
		else if (hasTag("ammo+"))
		{
			scene.increaseAmmo1();
		}
		makeDead();
	}

	if (otherGameObject.hasTag("enemy"))
	{
		if (hasTag("health+"))
		{
			scene.increaseHealth2();
		}
		else if (hasTag("ammo+"))
		{
			scene.increaseAmmo2();
		}
		makeDead();
	}

	makeDead();
}