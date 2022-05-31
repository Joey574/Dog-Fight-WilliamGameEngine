#include "Buff.h"

const float SPEED = 1.2f;

Buff::Buff()
{
	sf::Vector2f pos;
	sf::Vector2u size = GAME.getRenderWindow().getSize();

	pos.x = rand() % size.x;
	pos.y = rand() % size.y;
	
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
	else if (type == 3)
	{
		assignTag("flak+");
		sprite_.setTexture(GAME.getTexture("Resources/Flak.png"));
	}
	else if (type == 4)
	{
		assignTag("barrels+");
		sprite_.setTexture(GAME.getTexture("Resources/Trishot.png"));
	}
	else if(type == 5)
	{
		assignTag("shotgun+");
		sprite_.setTexture(GAME.getTexture("Resources/Shotgun.png"));
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
