#include "Buff.h"

const float SPEED = 1.2f;

Buff::Buff()
{
	sf::Vector2f pos;
	sf::Vector2u size = GAME.getRenderWindow().getSize();

	pos.x = rand() % size.x;
	pos.y = rand() % size.y;
	sprite_.setTexture(GAME.getTexture("Resources/meteor.png"));
	sprite_.setPosition(pos);
	type = (rand() % 2) + 1;
	if (type == 1)
	{
		assignTag("health+");
		sprite_.setTexture(GAME.getTexture("Resources/Health.png"));
	}
	else if (type == 2)
	{
		assignTag("ammo+");
		sprite_.setTexture(GAME.getTexture("Resources/Ammo.png"));
	}
}

void Buff::draw()
{
	GAME.getRenderWindow().draw(sprite_);
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