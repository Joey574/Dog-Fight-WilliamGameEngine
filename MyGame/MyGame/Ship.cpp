#include "Ship.h"

#include <memory>
#include "Laser.h"
#include "Ammo.h"
#include "GameScene.h"
#include <sstream>
#include <iostream>

const float SPEED = 0.4f;

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

	rotationSet(up, down, left, right);

	edgeCheck(x, y);

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

		int temp = 1;
		int rotation = sprite_.getRotation();

		float tempH = bounds.height;
		float tempW = bounds.width;

		rotationCheck(tempW, tempH, rotation);

		if (rotation == 0 || rotation == 180)
		{
			laserX = x + (tempW / 2.0f);
			laserY = y + (tempH / 3.5f);
		}
		else if (rotation == 90 || rotation == 270)
		{
			laserX = x + (tempW / 3.5f);
			laserY = y + (tempH / 2.0f);
		}
		else if (rotation == 45 || rotation == 225)
		{
			laserX = x + (tempW / 3.5f);
			laserY = y + (tempH / 2.0f);
		}
		else if (rotation == 135 || rotation == 315)
		{
			laserX = x + (tempW / 2.0f);
			laserY = y + (tempH / 3.5f);
		}

		LaserPtr laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);

		if (rotation == 0 || rotation == 180)
		{
			laserX = x + (tempW / 2.0f);
			laserY = y - (tempH / 3.5f);
		}
		else if (rotation == 90 || rotation == 270)
		{
			laserX = x - (tempW / 3.5f);
			laserY = y + (tempH / 2.0f);
		}
		else if(rotation == 45 || rotation == 225)
		{
			laserX = x + (tempW / 2.0f);
			laserY = y + (tempH / 3.5f);
		}
		else if (rotation == 135 || rotation == 315)
		{
			laserX = x + (tempW / 3.5f);
			laserY = y + (tempH / 2.0f);
		}

		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
	}
}

void Ship::laserShoot()
{

}

void Ship::triLaserShoot()
{

}

void Ship::flakShoot()
{

}

void Ship::shotgunShoot()
{

}

void Ship::edgeCheck(float x, float y)
{
	if (x - 42 > GAME.getRenderWindow().getSize().x)
	{
		x -= GAME.getRenderWindow().getSize().x + 42;
	}
	if (x + 42 < 0)
	{
		x += GAME.getRenderWindow().getSize().x + 42;
	}
	if (y - 60 > GAME.getRenderWindow().getSize().y)
	{
		y -= GAME.getRenderWindow().getSize().y + 60;
	}
	if (y + 60 < 0)
	{
		y += GAME.getRenderWindow().getSize().y + 60;
	}

	sprite_.setPosition(sf::Vector2f(x, y));
}

void Ship::rotationCheck(float& tempW, float& tempH, int rotation)
{
	if (rotation == 180)
	{
		tempW *= -1;
	}
	if (rotation == 270)
	{
		tempH *= -1;
	}
	if (rotation == 135)
	{
		tempW *= -1;
	}
	if (rotation == 225)
	{
		tempW *= -1;
		tempH *= -1;
	}
	if (rotation == 315)
	{
		tempH *= -1;
	}
}

void Ship::rotationSet(bool up, bool down, bool left, bool right)
{
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
}

sf::FloatRect Ship::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f Ship::shipPos()
{
	return sprite_.getPosition();
}

void Ship::handleCollision(GameObject& otherGameObject)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();


	if (otherGameObject.hasTag("health+"))
	{
		scene.increaseHealth2();
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("ammo+"))
	{
		scene.increaseAmmo2();
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("flak+"))
	{
		weapon_ = 2;
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("barrels+"))
	{
		weapon_ = 3;
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("shotgun+"))
	{
		weapon_ = 4;
		otherGameObject.makeDead();
	}
}