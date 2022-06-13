#include "Ships(plural).h"

#include <memory>
#include "Laser.h"
#include "Flak.h"
#include "Pellet.h"
#include "Flare.h"
#include "missile.h"
#include "Ammo.h"
#include "GameScene.h"
#include <sstream>
#include <iostream>

const float SPEED = 0.4f;
const int FLARE_DELAY = 100;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Ships::Ships(int x)
{
	ID = x;

	sprite_.setOrigin(sf::Vector2f(42, 60));

	if (ID == 0)
	{
		sprite_.setTexture(GAME.getTexture("Resources/ship.png"));
		sprite_.setPosition(sf::Vector2f(100, 100));

		assignTag("ship");
	}
	else if (ID == 1)
	{
		sprite_.setTexture(GAME.getTexture("Resources/enemy.png"));
		sprite_.setPosition(sf::Vector2f(730, 530));
		sprite_.setRotation(180);

		assignTag("enemy");
	}	
	else if (ID == 2)
	{
		sprite_.setTexture(GAME.getTexture("Resources/enemy.png"));
		sprite_.setPosition(sf::Vector2f(730, 530));
		sprite_.setRotation(180);

		assignTag("enemy");
	}
}

void Ships::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Ships::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	int msElapsed = elapsed.asMilliseconds();

	rotation = sprite_.getRotation();

	if (hasTag("ship"))
	{
		scene.setShipPos(sprite_.getPosition());
	}
	if (hasTag("enemy"))
	{
		scene.setEnemyPos(sprite_.getPosition());
	}

	shipMove(msElapsed);
}

void Ships::shipMove(int msElapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	if (ID == 0)
	{
		if (scene.getHealth1() <= 0)
		{
			makeDead();
		}
	}
	else if (ID == 1)
	{
		if (scene.getHealth2() <= 0)
		{
			makeDead();
		}
	}

	if (ID == 0)
	{
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
	}
	else if (ID == 1)
	{
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
	}
	else if (ID == 2)
	{
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		sf::Vector2f target = scene.getShipPos();
		if (target.y < pos.y)
		{
			y -= SPEED * msElapsed;
			up = true;
		}
		if (target.y > pos.y)
		{
			y += SPEED * msElapsed;
			down = true;
		}
		if (target.x < pos.x)
		{
			x -= SPEED * msElapsed;
			left = true;
		}
		if (target.x > pos.x)
		{
			x += SPEED * msElapsed;
			right = true;
		}
	}

	rotationSet(up, down, left, right);

	edgeCheck(x, y);

	if (fireTimer_ > 0)
	{
		fireTimer_ -= msElapsed;
	}

	if (ammo_ < 1 && weapon_ != 1)
	{
		FIRE_DELAY = 200;
		weapon_ = 1;
		ammo_ = 100;
		
		if (ID == 0)
		{
			scene.setAmmo1(100);
		}
		else if (ID == 1)
		{
			scene.setAmmo2(100);
		}
	}
	
	if (ID == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && flareTimer_ <= 0 && flares_ > 0)
		{
			flareShoot();
		}
	}
	else if (ID == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && flareTimer_ <= 0 && flares_ > 0)
		{
			flareShoot();
		}
	}

	if (ID == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && fireTimer_ <= 0 && ammo_ > 0)
		{
			pew_.setVolume(10);
			pew_.setBuffer(GAME.getSoundBuffer("Resources/pew 2.wav"));
			pew_.play();
			fireTimer_ = FIRE_DELAY;

			if (weapon_ == 1)
			{
				laserShoot();
			}
			else if (weapon_ == 2)
			{
				flakShoot();
			}
			else if (weapon_ == 3)
			{
				triLaserShoot();
			}
			else if (weapon_ == 4)
			{
				shotgunShoot();
			}
			else if (weapon_ == 5)
			{
				missileshoot();
			}
		}
	}
	else if (ID == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && fireTimer_ <= 0 && ammo_ > 0)
		{
			pew_.setBuffer(GAME.getSoundBuffer("Resources/pew 2.wav"));
			pew_.play();
			fireTimer_ = FIRE_DELAY;

			if (weapon_ == 1)
			{
				laserShoot();
			}
			else if (weapon_ == 2)
			{
				flakShoot();
			}
			else if (weapon_ == 3)
			{
				triLaserShoot();
			}
			else if (weapon_ == 4)
			{
				shotgunShoot();
			}
			else if (weapon_ == 5)
			{
				missileshoot();
			}
		}
	}

	if (ID == 2) // AI
	{
		GameScene& scene = (GameScene&)GAME.getCurrentScene();
		sf::Vector2f target = scene.getShipPos();
		if ((target.x - 10.0f) < pos.x < (target.x + 10.0f) && (target.y - 10.0f) < pos.y < (target.y + 10.0f) && fireTimer_ <= 0 && scene.getAmmo2() > 0)
		{
			pew_.setBuffer(GAME.getSoundBuffer("Resources/pew 2.wav"));
			pew_.play();

			fireTimer_ = FIRE_DELAY;

			if (weapon_ == 1)
			{
				laserShoot();
			}
			else if (weapon_ == 2)
			{
				flakShoot();
			}
			else if (weapon_ == 3)
			{
				triLaserShoot();
			}
			else if (weapon_ == 4)
			{
				shotgunShoot();
			}
			else if (weapon_ == 5)
			{
				missileshoot();
			}
		}
	}
}

void Ships::laserShoot()
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos;

	pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	bounds = sprite_.getGlobalBounds();

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

	if (ammo_ > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID == 1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
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

	if (ammo_ > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID == 1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
	}
}

void Ships::triLaserShoot()
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	LaserPtr laser;

	sf::Vector2f pos;

	pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	bounds = sprite_.getGlobalBounds();

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

	if (ammo_ > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID ==1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
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

	if (ammo_ > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID == 1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
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

	if (ammo_ > 0)
	{
		laser = std::make_shared<Laser>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(laser);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID == 1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
	}
}

void Ships::flakShoot()
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos;

	pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	bounds = sprite_.getGlobalBounds();

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
		laserX = x + (tempW / 2.5f);
		laserY = y + (tempH / 2.5f);
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
		rotation -= 8;
	}
	else if (temp == 5)
	{
		rotation += 8;
	}

	for (int x = 0; rotation > 360; x++)
	{
		rotation -= 360;
	}
	for (int x = 0; rotation < 0; x++)
	{
		rotation += 360;
	}

	if (ammo_ > 0)
	{
		flak = std::make_shared<Flak>(sf::Vector2f(laserX, laserY), rotation);
		GAME.getCurrentScene().addGameObject(flak);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID == 1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
	}

}

void Ships::shotgunShoot()
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos;

	pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	bounds = sprite_.getGlobalBounds();

	PelletPtr pellet;

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

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
		laserX = x + (tempW / 2.0f);
		laserY = y + (tempH / 2.0f);
	}

	for (int x = 0; rotation > 360; x++)
	{
		rotation -= 360;
	}
	for (int x = 0; rotation < 0; x++)
	{
		rotation += 360;
	}

	for (int i = rotation - 10; i < rotation + 11; i += 5)
	{
		if (ammo_ > 0)
		{
			pellet = std::make_shared<Pellet>(sf::Vector2f(laserX, laserY), i);
			GAME.getCurrentScene().addGameObject(pellet);
			ammo_--;

			if (ID == 0)
			{
				scene.setAmmo1(ammo_);
			}
			else if (ID == 1 || ID == 2)
			{
				scene.setAmmo2(ammo_);
			}
		}
	}
}

void Ships::missileshoot()
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	MissilePtr missile;

	sf::Vector2f pos;

	pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	bounds = sprite_.getGlobalBounds();

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

	if (ammo_ > 0)
	{
		missile = std::make_shared<Missile>(sf::Vector2f(laserX, laserY), rotation, ID, bounds);
		GAME.getCurrentScene().addGameObject(missile);
		ammo_--;

		if (ID == 0)
		{
			scene.setAmmo1(ammo_);
		}
		else if (ID == 1 || ID == 2)
		{
			scene.setAmmo2(ammo_);
		}
	}
}

void Ships::flareShoot()
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos;

	pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	sf::FloatRect bounds;

	bounds = sprite_.getGlobalBounds();

	FlarePtr flares;

	float laserX;
	float laserY;

	float tempH = bounds.height;
	float tempW = bounds.width;

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
		laserX = x + (tempW / 2.0f);
		laserY = y + (tempH / 2.0f);
	}

	for (int x = 0; rotation > 360; x++)
	{
		rotation -= 360;
	}
	for (int x = 0; rotation < 0; x++)
	{
		rotation += 360;
	}

	for (int i = rotation - 10; i < rotation + 11; i += 5)
	{
		if (ammo_ > 0)
		{
			flares = std::make_shared<Flare>(sf::Vector2f(laserX, laserY), i);
			GAME.getCurrentScene().addGameObject(flares);
			flares_--;

			if (ID == 0)
			{
				//scene.setAmmo1(ammo_);
			}
			else if (ID == 1)
			{
				//scene.setAmmo2(ammo_);
			}
		}
	}
}

// Eric you are very cool :)

void Ships::edgeCheck(float x, float y)
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

void Ships::rotationSet(bool up, bool down, bool left, bool right)
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

void Ships::handleCollision(GameObject& otherGameObject)
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
		ammo_ = 100;

		if (ID == 0)
		{
			scene.setAmmo1(100);
		}
		else
		{
			scene.setAmmo2(100);
		}
		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("flak+"))
	{
		FIRE_DELAY = 80;
		weapon_ = 2;

		otherGameObject.makeDead();
	}
	if (otherGameObject.hasTag("barrels+"))
	{
		FIRE_DELAY = 200;
		weapon_ = 3;

		otherGameObject.makeDead();
	}
	//if (otherGameObject.hasTag("shotgun+"))
	//{
	//	FIRE_DELAY = 300;
	//	weapon_ = 4;

	//	otherGameObject.makeDead();
	//}
	if (otherGameObject.hasTag("shotgun+"))
	{
		FIRE_DELAY = 500;
		weapon_ = 5;

		otherGameObject.makeDead();
	}
}

sf::FloatRect Ships::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}