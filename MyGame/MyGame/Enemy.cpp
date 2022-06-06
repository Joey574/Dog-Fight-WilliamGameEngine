#include "Enemy.h"

#include <memory>
#include "Laser.h"
#include "Flak.h"
#include "Pellet.h"
#include "Ammo.h"
#include "GameScene.h"
#include <sstream>
#include <iostream>

const float SPEED = 0.4f;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Enemy::Enemy()
{
	sprite_.setRotation(180);
	sprite_.setOrigin(sf::Vector2f(42, 60));
	sprite_.setTexture(GAME.getTexture("Resources/enemy.png"));
	sprite_.setPosition(sf::Vector2f(730, 530));
	assignTag("enemy");
}

void Enemy::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Enemy::update(sf::Time& elapsed)
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

	if (scene.getHealth2() < 1)
	{
		makeDead();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		y -= SPEED * msElapsed;
		up = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		y += SPEED * msElapsed;
		down = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		x -= SPEED * msElapsed;
		left = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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

	if (scene.getAmmo2() < 1 && weapon_ != 1)
	{
		FIRE_DELAY = 200;
		weapon_ = 1;
		scene.increaseAmmo2();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && fireTimer_ <= 0 && scene.getAmmo2() > 0)
	{
		fireTimer_ = FIRE_DELAY;

		if (weapon_ == 1)
		{
			ammoReturn = laserShoot(scene.getAmmo2());
		}
		else if (weapon_ == 2)
		{
			ammoReturn = flakShoot(scene.getAmmo2());
		}
		else if (weapon_ == 3)
		{
			ammoReturn = triLaserShoot(scene.getAmmo2());
		}
		else if (weapon_ == 4)
		{
			ammoReturn = shotgunShoot(scene.getAmmo2());
		}

		scene.decreaseAmmo2(scene.getAmmo2() - ammoReturn);
	}
}

int Enemy::laserShoot(int ammo)
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

int Enemy::triLaserShoot(int ammo)
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

int Enemy::flakShoot(int ammo)
{
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds = sprite_.getGlobalBounds();

	FlakPtr flak;

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

	int temp = rand() % 6;

	rotationCheck(tempW, tempH, rotation);

	if (rotation == 0 || rotation == 180)
	{
		laserX = x + (tempW / 1.75f);
		laserY = y;
	}
	else if (rotation == 90 || rotation == 270)
	{
		laserX = x;
		laserY = y + (tempH / 1.75f);
	}
	else
	{
		laserX = x + (tempW / 3.5f);
		laserY = y + (tempH / 3.5f);
	}

	if (temp == 0)
	{
		rotation += 5;
	}
	else if (temp == 1)
	{
		rotation -= 5;
	}
	else if (temp == 2)
	{
		rotation -= 10;
	}
	else if (temp == 3)
	{
		rotation += 10;
	}
	else if (temp == 4)
	{
		rotation -= 15;
	}
	else if (temp == 5)
	{
		rotation += 15;
	}

	for (int i = 0; rotation > 360; i++)
	{
		rotation -= 360;
	}
	for (int i = 0; rotation < 360; i++)
	{
		rotation += 360;
	}

	if (ammo > 0)
	{
		flak = std::make_shared<Flak>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(flak);
		ammo--;
	}

	return ammo;

}

int Enemy::shotgunShoot(int ammo)
{
	return ammo;
}

sf::FloatRect Enemy::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Enemy::handleCollision(GameObject& otherGameObject)
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

void Enemy::edgeCheck(float x, float y)
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

void Enemy::rotationCheck(float& tempW, float& tempH, int rotation)
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

void Enemy::rotationSet(bool up, bool down, bool left, bool right)
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