#include "Ship.h"

#include <memory>
#include "Laser.h"

const float SPEED = 0.4f;
const int FIRE_DELAY = 200;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Ship::Ship()
{
	sprite_.setOrigin(sf::Vector2f(56.5, 56.5));
	sprite_.setTexture(GAME.getTexture("Resources/ship.png"));
	sprite_.setPosition(sf::Vector2f(100, 100));

}

void Ship::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Ship::update(sf::Time& elapsed)
{
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	int msElapsed = elapsed.asMilliseconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		y -= SPEED * msElapsed;
		sprite_.setRotation(270);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		y += SPEED * msElapsed;
		sprite_.setRotation(90);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x -= SPEED * msElapsed;
		sprite_.setRotation(180);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		x += SPEED * msElapsed;
		sprite_.setRotation(0);
	}

	sprite_.setPosition(sf::Vector2f(x, y));

	if (fireTimer_ > 0)
	{
		fireTimer_ -= msElapsed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireTimer_ <= 0)
	{
		fireTimer_ = FIRE_DELAY;

		sf::FloatRect bounds = sprite_.getGlobalBounds();

		float laserX = x + (bounds.width / 3.5f);
		float laserY = y + (bounds.height / 3.5f);

		LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), sprite_.getRotation());
		GAME.getCurrentScene().addGameObject(laser);

		laserX = x + (bounds.width / 3.5f);
		laserY = y - (bounds.height / 3.5f);

		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), sprite_.getRotation());
		GAME.getCurrentScene().addGameObject(laser);
	}
}

sf::FloatRect Ship::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}