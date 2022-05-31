#include "Enemy.h"

#include <memory>
#include "Laser.h"
#include "Ammo.h"
#include "GameScene.h"
#include <sstream>

const float SPEED = 0.4f;
const int FIRE_DELAY = 200;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Enemy::Enemy()
{
	sprite_.setRotation(180);
	sprite_.setOrigin(sf::Vector2f(56.5, 56.5));
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
	int weaptime;
	
	GameScene& scene = (GameScene&)GAME.getCurrentScene();
	sf::Vector2f pos = sprite_.getPosition();
	float x = pos.x;
	float y = pos.y;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && fireTimer_ <= 0 && scene.getAmmo2() > 0)
	{
		int shotsf = 2;
		scene.decreaseAmmo2(shotsf);
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

		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
	}
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