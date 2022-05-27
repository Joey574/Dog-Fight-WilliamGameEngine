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
	sprite_.setOrigin(sf::Vector2f(42, 60));
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

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	int msElapsed = elapsed.asMilliseconds();

	if (scene.getHealth1() < 1)
	{
		makeDead();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		y -= SPEED * msElapsed;
		up = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		y += SPEED * msElapsed;
		down = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		x -= SPEED * msElapsed;
		left = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		x += SPEED * msElapsed;
		right = true;
	}

	if (up && left)
	{
		sprite_.setRotation(225);
	}
	else if (up && right)
	{
		sprite_.setRotation(315);
	}
	else if (down && left)
	{
		sprite_.setRotation(135);
	}
	else if (down && right)
	{
		sprite_.setRotation(45);
	}
	else if (down)
	{
		sprite_.setRotation(90);
	}
	else if (up)
	{
		sprite_.setRotation(270);
	}
	else if (left)
	{
		sprite_.setRotation(180);
	}
	else if (right)
	{
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && fireTimer_ <= 0 && scene.getAmmo1() > 0)
	{
		int shotsf = 2;
		scene.decreaseAmmo1(shotsf);
		fireTimer_ = FIRE_DELAY;

		sf::FloatRect bounds = sprite_.getGlobalBounds();

		float laserX;
		float laserY;

		if (sprite_.getRotation() == 0 || sprite_.getRotation() == 180)
		{
			laserX = x;
			laserY = y + (bounds.height / 3.5f);
		}
		else if (sprite_.getRotation() == 90 || sprite_.getRotation() == 270)
		{
			laserX = x + (bounds.width / 3.5f);
			laserY = y;
		}
		else if (sprite_.getRotation() == 45 || sprite_.getRotation() == 315)
		{
			laserX = x + (bounds.width / 3.5f);
			laserY = y + (bounds.height / 3.5f);
		}

		LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), sprite_.getRotation());
		GAME.getCurrentScene().addGameObject(laser);

		if (sprite_.getRotation() == 0 || sprite_.getRotation() == 180)
		{
			laserX = x;
			laserY = y - (bounds.height / 3.5f);
		}
		else if (sprite_.getRotation() == 90 || sprite_.getRotation() == 270)
		{
			laserX = x - (bounds.width / 3.5f);
			laserY = y;
		}

		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), sprite_.getRotation());
		//GAME.getCurrentScene().addGameObject(laser);
	}
}

sf::FloatRect Ship::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f Ship::shipPos()
{
	return sprite_.getPosition();
}
