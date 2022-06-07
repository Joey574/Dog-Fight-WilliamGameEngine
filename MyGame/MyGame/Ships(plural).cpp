#include "Ships(plural).h"

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

Ships::Ships()
{
	sprite_1.setOrigin(sf::Vector2f(42, 60));
	sprite_2.setOrigin(sf::Vector2f(42, 60));

	sprite_1.setTexture(GAME.getTexture("Resources/ship.png"));
	sprite_2.setTexture(GAME.getTexture("Resources/enemy.png"));

	sprite_1.setPosition(sf::Vector2f(100, 100));
	sprite_2.setPosition(sf::Vector2f(730, 530));

	assignTag("ship");
}

void Ships::draw()
{
	GAME.getRenderWindow().draw(sprite_1);
	GAME.getRenderWindow().draw(sprite_2);
}

void Ships::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();

	rotation1 = sprite_1.getRotation();
	rotation2 = sprite_2.getRotation();

	shipMove(msElapsed);

	enemyMove(msElapsed);
}

void Ships::shipMove(int msElapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();
	sf::Vector2f pos = sprite_1.getPosition();
	float x = pos.x;
	float y = pos.y;

	int ammoReturn;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

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

	rotationSet(up, down, left, right, 0);

	edgeCheck(x, y, 0);

	if (fireTimer_1 > 0)
	{
		fireTimer_1 -= msElapsed;
	}

	if (scene.getAmmo1() < 1 && weapon_1 != 1)
	{
		FIRE_DELAY1 = 200;
		weapon_1 = 1;
		scene.increaseAmmo1();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && fireTimer_1 <= 0 && scene.getAmmo1() > 0)
	{
		fireTimer_1 = FIRE_DELAY1;

		if (weapon_1 == 1)
		{
			ammoReturn = laserShoot(scene.getAmmo1(), 0);
		}
		else if (weapon_1 == 2)
		{
			ammoReturn = flakShoot(scene.getAmmo1(), 0);
		}
		else if (weapon_1 == 3)
		{
			ammoReturn = triLaserShoot(scene.getAmmo1(), 0);
		}
		else if (weapon_1 == 4)
		{
			ammoReturn = shotgunShoot(scene.getAmmo1(), 0);
		}

		scene.decreaseAmmo1(scene.getAmmo1() - ammoReturn);
	}
}

void Ships::enemyMove(int msElapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();
	sf::Vector2f pos = sprite_2.getPosition();
	float x = pos.x;
	float y = pos.y;

	int ammoReturn;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

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

	rotationSet(up, down, left, right, 1);

	edgeCheck(x, y, 1);

	if (fireTimer_2 > 0)
	{
		fireTimer_2 -= msElapsed;
	}

	if (scene.getAmmo2() < 1 && weapon_2 != 1)
	{
		FIRE_DELAY2 = 200;
		weapon_2 = 1;
		scene.increaseAmmo2();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && fireTimer_2 <= 0 && scene.getAmmo2() > 0)
	{
		fireTimer_2 = FIRE_DELAY2;

		if (weapon_2 == 1)
		{
			ammoReturn = laserShoot(scene.getAmmo2(), 1);
		}
		else if (weapon_2 == 2)
		{
			ammoReturn = flakShoot(scene.getAmmo2(), 1);
		}
		else if (weapon_2 == 3)
		{
			ammoReturn = triLaserShoot(scene.getAmmo2(), 1);
		}
		else if (weapon_2 == 4)
		{
			ammoReturn = shotgunShoot(scene.getAmmo2(), 1);
		}

		scene.decreaseAmmo2(scene.getAmmo2() - ammoReturn);
	}
}

int Ships::laserShoot(int ammo, int ID)
{
	sf::Vector2f pos;

	if (ID == 0)
	{
		pos = sprite_1.getPosition();
	}
	else
	{
		pos = sprite_2.getPosition();
	}

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	if (ID == 0)
	{
		bounds = sprite_1.getGlobalBounds();
	}
	else
	{
		bounds = sprite_2.getGlobalBounds();
	}

	LaserPtr laser;

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

	int rotation;

	if (ID == 0)
	{
		rotation = sprite_1.getRotation();
	}
	else
	{
		rotation = sprite_2.getRotation();
	}

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

int Ships::triLaserShoot(int ammo, int ID)
{
	LaserPtr laser;

	sf::Vector2f pos;

	if (ID == 0)
	{
		pos = sprite_1.getPosition();
	}
	else
	{
		pos = sprite_2.getPosition();
	}

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	if (ID == 0)
	{
		bounds = sprite_1.getGlobalBounds();
	}
	else
	{
		bounds = sprite_2.getGlobalBounds();
	}

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

	int rotation;

	if (ID == 0)
	{
		rotation = sprite_1.getRotation();
	}
	else
	{
		rotation = sprite_2.getRotation();
	}

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

int Ships::flakShoot(int ammo, int ID)
{
	sf::Vector2f pos;

	if (ID == 0)
	{
		pos = sprite_1.getPosition();
	}
	else
	{
		pos = sprite_2.getPosition();
	}

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	if (ID == 0)
	{
		bounds = sprite_1.getGlobalBounds();
	}
	else
	{
		bounds = sprite_2.getGlobalBounds();
	}

	FlakPtr flak;

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

	int temp = rand() % 6;

	int rotation;

	if (ID == 0)
	{
		rotation = sprite_1.getRotation();
	}
	else
	{
		rotation = sprite_2.getRotation();
	}

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

int Ships::shotgunShoot(int ammo, int ID)
{
	return ammo;
}

// Eric you are very cool :)

void Ships::edgeCheck(float x, float y, int ID)
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

	if (ID == 0)
	{
		sprite_1.setPosition(sf::Vector2f(x, y));

	}
	else
	{
		sprite_2.setPosition(sf::Vector2f(x, y));
	}
}

void Ships::rotationCheck(float& tempW, float& tempH, int rotation)
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
		tempH *= -1;
		tempW *= -1;
	}
	if (rotation == 315)
	{
		tempH *= -1;
	}
}

void Ships::rotationSet(bool up, bool down, bool left, bool right, int ID)
{
	if (up && left)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(225);
		}
		else
		{
			sprite_2.setRotation(225);
		}
	}
	else if (up && right)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(315);
		}
		else
		{
			sprite_2.setRotation(315);
		}
	}
	else if (down && left)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(135);
		}
		else
		{
			sprite_2.setRotation(135);
		}
	}
	else if (down && right)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(45);
		}
		else
		{
			sprite_2.setRotation(45);
		}
	}
	else if (down)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(90);
		}
		else
		{
			sprite_2.setRotation(90);
		}
	}
	else if (up)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(270);
		}
		else
		{
			sprite_2.setRotation(270);
		}
	}
	else if (left)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(180);
		}
		else
		{
			sprite_2.setRotation(180);
		}
	}
	else if (right)
	{
		if (ID == 0)
		{
			sprite_1.setRotation(0);
		}
		else
		{
			sprite_2.setRotation(0);
		}
	}
}

void Ships::handleCollision(GameObject& otherGameObject, int ID)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	if (otherGameObject.hasTag("health+"))
	{
		if (ID == 0)
		{
			scene.increaseHealth1();
		}
		else
		{
			scene.increaseHealth2();
		}
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("ammo+"))
	{
		if (ID == 0)
		{
			scene.increaseAmmo1();
		}
		else
		{
			scene.increaseAmmo2();
		}
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("flak+"))
	{
		if (ID == 0)
		{
			FIRE_DELAY1 = 100;
			weapon_1 = 2;
		}
		else
		{
			FIRE_DELAY2 = 100;
			weapon_2 = 2;
		}
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("barrels+"))
	{
		if (ID == 0)
		{
			FIRE_DELAY1 = 200;
			weapon_1 = 3;
		}
		else
		{
			FIRE_DELAY2 = 200;
			weapon_2 = 3;
		}
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("shotgun+"))
	{
		if (ID == 0)
		{
			FIRE_DELAY1 = 300;
			weapon_1 = 4;
		}
		else
		{
			FIRE_DELAY2 = 300;
			weapon_2 = 4;
		}
		otherGameObject.makeDead();
	}
}

sf::FloatRect Ships::getShipCollisionRect()
{
	return sprite_1.getGlobalBounds();
}

sf::FloatRect Ships::getEnemyCollisionRect()
{
	return sprite_2.getGlobalBounds();
}

sf::Vector2f Ships::shipPos()
{
	return sprite_1.getPosition();
}

sf::Vector2f Ships::enemyPos()
{
	return sprite_2.getPosition();
}