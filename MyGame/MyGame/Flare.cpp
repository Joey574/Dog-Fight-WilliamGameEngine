#define _USE_MATH_DEFINES
#include "math.h"
#include "Flare.h"

const float SPEED = 1.3f;

Flare::Flare(sf::Vector2f pos, int rot)
{
	sprite_.setTexture(GAME.getTexture("Resources/flare.png"));
	sprite_.setPosition(pos);
	sprite_.setRotation(rot);
	assignTag("Flare");
}

void Flare::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Flare::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();
	timer_ -= msElapsed;
	if (timer_ > 900)
	{
		move(elapsed);
	}
	if (timer_ <= 0)
	{
		makeDead();
	}
}

void Flare::move(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();

	int rotation = sprite_.getRotation();

	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x > GAME.getRenderWindow().getSize().x || pos.y > GAME.getRenderWindow().getSize().y || pos.x < 0 || pos.y < 0)
	{
		makeDead();
	}

	if (rotation == 0 || rotation == 180)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0), pos.y));
	}
	else if (rotation == 90 || rotation == 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x, pos.y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0)));
	}
	else if (rotation > 0 && rotation < 90 || rotation > 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0)));
	}
	else if (rotation > 90 && rotation < 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0)));
	}
}

sf::FloatRect Flare::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}
