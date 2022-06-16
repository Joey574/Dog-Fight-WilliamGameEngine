#define _USE_MATH_DEFINES
#include <math.h>
#include "Missile.h"
#include <iostream>

Missile::Missile(sf::Vector2f pos, int rot, int ID)
{
	SPEED = 1.25f;

	sprite_.setTexture(GAME.getTexture("Resources/missile.png"));
	sprite_.setPosition(pos);
	sprite_.setRotation(rot);
	assignTag("missile");
	setID(ID);
}

void Missile::setID(int ID)
{
	ID_ = ID;
}

void Missile::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Missile::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f Target;

	rotation = sprite_.getRotation();

	int msElapsed = elapsed.asMilliseconds();

	sf::Vector2f pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	if (ID_ == 0)
	{
		Target = scene.getEnemyPos();
	}
	else if (ID_ == 1 || ID_ == 2) //Hi Joey!!!!!!!!!!!!!!!!!!!! You are silly
	{
		Target = scene.getShipPos();
	}

	if (pos.x > GAME.getRenderWindow().getSize().x || pos.y > GAME.getRenderWindow().getSize().y || pos.x < 0 || pos.y < 0)
	{
		makeDead();
	}

	if (forwardTime <= 0)
	{
		SPEED = 0.4f;
	}

	if (forwardTime > 0)
	{
		forwardTime -= msElapsed;

		x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0);
		y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0);
	}
	else
	{
		rotationSet(pos, Target);

		y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0);
		x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0);
	}

	sprite_.setPosition(x, y);
}

sf::FloatRect Missile::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Missile::handleCollision(GameObject& otherGameObject)
{
	float dam = 3;

	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos = sprite_.getPosition();

	ExplosionPtr explosion = std::make_shared<Explosion>(sprite_.getPosition());

	if (otherGameObject.hasTag("ship"))
	{
		GAME.getCurrentScene().addGameObject(explosion);
		scene.decreaseHealth1(dam);
	}

	if (otherGameObject.hasTag("enemy"))
	{
		GAME.getCurrentScene().addGameObject(explosion);
		scene.decreaseHealth2(dam);
	}

	if (otherGameObject.hasTag("flare"))
	{
		GAME.getCurrentScene().addGameObject(explosion);
		otherGameObject.makeDead();
		makeDead();
	}

	if (!otherGameObject.hasTag("Missile"))
	{
		makeDead();
	}
}

void Missile::rotationSet(sf::Vector2f pos, sf::Vector2f Target)
{	
	float xDif = (pos.x - Target.x);
	float yDif = (pos.y - Target.y);

	float rotationSet = atan((xDif / yDif) * M_PI / 180.0f);

	std::cout << "\nRotation difference (in degrees): " << atan((yDif / xDif)) << "\nRotation difference (in radians): " << rotationSet;

	sprite_.setRotation(rotationSet);
}
