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

	int ammoReturn;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	rotation = sprite_.getRotation();

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

	if (scene.getAmmo1() < 1 && weapon_ != 1)
	{
		FIRE_DELAY = 200;
		weapon_ = 1;
		scene.increaseAmmo1();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && fireTimer_ <= 0 && scene.getAmmo1() > 0)
	{
		fireTimer_ = FIRE_DELAY;

		if (weapon_ == 1)
		{
			//ammoReturn = laserShoot(scene.getAmmo1());
			ammoReturn = flakShoot(scene.getAmmo1());			
		}
		else if (weapon_ == 2)
		{
			ammoReturn = flakShoot(scene.getAmmo1());
		}
		else if (weapon_ == 3)
		{
			ammoReturn = triLaserShoot(scene.getAmmo1());
		}
		else if (weapon_ == 4)
		{
			ammoReturn = shotgunShoot(scene.getAmmo1());
		}

		scene.decreaseAmmo1(scene.getAmmo1() - ammoReturn);
	}
}

int Ship::laserShoot(int ammo)
{

	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds = sprite_.getGlobalBounds();

	LaserPtr laser;

	float laserX;
	float laserY;

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

	if (ammo > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo--;
	}


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
	else if (rotation == 45 || rotation == 225)
	{
		laserX = x + (tempW / 2.0f);
		laserY = y + (tempH / 3.5f);
	}
	else if (rotation == 135 || rotation == 315)
	{
		laserX = x + (tempW / 3.5f);
		laserY = y + (tempH / 2.0f);
	}

	if (ammo > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo--;
	}

	return ammo;

}

int Ship::triLaserShoot(int ammo)
{
	LaserPtr laser;

	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds = sprite_.getGlobalBounds();

	float laserX;
	float laserY;

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

	if (ammo > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo--;
	}

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
	else if (rotation == 45 || rotation == 225)
	{
		laserX = x + (tempW / 2.0f);
		laserY = y + (tempH / 3.5f);
	}
	else if (rotation == 135 || rotation == 315)
	{
		laserX = x + (tempW / 3.5f);
		laserY = y + (tempH / 2.0f);
	}

	if (ammo > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo--;
	}

	if (rotation == 0 || rotation == 180)
	{
		laserX = x + (tempW / 2.0f);
		laserY = y;
	}
	else if (rotation == 90 || rotation == 270)
	{
		laserX = x;
		laserY = y + (tempH / 2.0f);
	}
	else if (rotation == 45 || rotation == 225)
	{
		laserX = x + (tempW / 2.0f);
		laserY = y;
	}
	else if (rotation == 135 || rotation == 315)
	{
		laserX = x;
		laserY = y + (tempH / 2.0f);
	}

	if (ammo > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo--;
	}

	return ammo;

}

int Ship::flakShoot(int ammo)
{
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds = sprite_.getGlobalBounds();

	LaserPtr laser;

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

	int temp = rand() % 3;

	if (temp == 0)
	{
		rotation += 15;
	}
	else if (temp == 1)
	{
		rotation -= 15;
	}

	if (rotation == 360)
	{
		rotation = 0;
	}
	if (rotation == -15)
	{
		rotation == 345;
	}

	rotationCheck(tempW, tempH, rotation);

	if (rotation == 0 || rotation == 180)
	{
		laserX = x + (tempW / 2.0f);
		laserY = y;
	}
	else if (rotation == 90 || rotation == 270)
	{
		laserX = x;
		laserY = y + (tempH / 2.0f);
	}
	else if (rotation == 15 || rotation == 345)
	{
		laserX = x + (tempW / 2.0f);
		laserY = y + (tempH / 3.5f);
	}
	else if (rotation == 135 || rotation == 315)
	{
		laserX = x + (tempW / 3.5f);
		laserY = y + (tempH / 2.0f);
	}
	else
	{
		laserY = 0;
		laserX = 0;
		std::cout << rotation << "\n";
	}

	if (ammo > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo--;
	}

	return ammo;

}

int Ship::shotgunShoot(int ammo)
{
	return ammo;
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
		scene.increaseHealth1();
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("ammo+"))
	{
		scene.increaseAmmo1();
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("flak+"))
	{
		FIRE_DELAY = 100;
		weapon_ = 2;
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("barrels+"))
	{
		FIRE_DELAY = 200;
		weapon_ = 3;
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("shotgun+"))
	{
		FIRE_DELAY = 300;
		weapon_ = 4;
		otherGameObject.makeDead();
	}
}