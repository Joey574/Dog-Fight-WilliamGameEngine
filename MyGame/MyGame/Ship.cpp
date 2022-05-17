#include "Ship.h"

#include <memory>
#include "Laser.h"
#include "Ammo.h"
#include "GameScene.h"
#include <sstream>

const float SPEED = 0.4f;
const int FIRE_DELAY = 200;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Ship::Ship()
{
	sprite_.setOrigin(sf::Vector2f(56.5, 56.5));
	sprite_.setTexture(GAME.getTexture("Resources/ship.png"));
	sprite_.setPosition(sf::Vector2f(100, 100));
	assignTag("ship");
}

void Ship::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Ship::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	int msElapsed = elapsed.asMilliseconds();

	int ammo = scene.getAmmo();

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

	if (x - 50 > GAME.getRenderWindow().getSize().x)
	{
		x -= GAME.getRenderWindow().getSize().x + 50;
	}
	if (x + 50 < 0)
	{
		x += GAME.getRenderWindow().getSize().x + 50;
	}
	if (y - 50 > GAME.getRenderWindow().getSize().y)
	{
		y -= GAME.getRenderWindow().getSize().y + 50;
	}
	if (y + 50 < 0)
	{
		y += GAME.getRenderWindow().getSize().y + 50;
	}

	sprite_.setPosition(sf::Vector2f(x, y));

	if (fireTimer_ > 0)
	{
		fireTimer_ -= msElapsed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fireTimer_ <= 0 && scene.getAmmo() > 0)
	{
		scene.decreaseAmmo();
		fireTimer_ = FIRE_DELAY;

		sf::FloatRect bounds = sprite_.getGlobalBounds();

		float laserX;
		float laserY;

		if (sprite_.getRotation() == 0)
		{
			laserX = x + (bounds.width / 3.5f) + 5;
			laserY = y + (bounds.height / 3.5f) - 5;
		}
		else if (sprite_.getRotation() == 180)
		{
			laserX = x + (bounds.width / 3.5f) - 55;
			laserY = y + (bounds.height / 3.5f) - 6;
		}
		else if (sprite_.getRotation() == 90)
		{
			laserX = x + (bounds.width / 3.5f) - 5;
			laserY = y + (bounds.height / 3.5f) + 10;
		}
		else if (sprite_.getRotation() == 270)
		{
			laserX = x + (bounds.width / 3.5f) - 6;
			laserY = y + (bounds.height / 3.5f) - 60;
		}

		LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), sprite_.getRotation());
		GAME.getCurrentScene().addGameObject(laser);

		if (sprite_.getRotation() == 0)
		{
			laserX = x + (bounds.width / 3.5f) + 5;
			laserY = y - (bounds.height / 3.5f) + 8;
		}
		else if (sprite_.getRotation() == 180)
		{
			laserX = x + (bounds.width / 3.5f) - 55;
			laserY = y - (bounds.height / 3.5f) + 7;
		}
		else if (sprite_.getRotation() == 90)
		{
			laserX = x - (bounds.width / 3.5f) + 5;
			laserY = y + (bounds.height / 3.5f) + 10;
		}
		else if (sprite_.getRotation() == 270)
		{
			laserX = x - (bounds.width / 3.5f) + 8;
			laserY = y + (bounds.height / 3.5f) - 60;
		}

		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), sprite_.getRotation());
		GAME.getCurrentScene().addGameObject(laser);
	}
}

sf::FloatRect Ship::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}