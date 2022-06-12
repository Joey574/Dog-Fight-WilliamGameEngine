#define _USE_MATH_DEFINES
#include "math.h"
#include "Missile.h"

const float SPEED = 1.3f;

Missile::Missile(sf::Vector2f pos, int rot)
{
	sprite_.setTexture(GAME.getTexture("Resources/missile.png"));
	sprite_.setPosition(pos);
	sprite_.setRotation(rot);
	assignTag("missile");
}

void Missile::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Missile::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f Target;

	int msElapsed = elapsed.asMilliseconds();

	int rotation = sprite_.getRotation();

	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x > GAME.getRenderWindow().getSize().x || pos.y > GAME.getRenderWindow().getSize().y || pos.x < 0 || pos.y < 0)
	{
		makeDead();
	}

	if (rotation == 0 || rotation == 180)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0), pos.y));
	}
	else if (rotation == 90 || rotation == 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x, pos.y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0)));
	}
	else if (rotation > 0 && rotation < 90 || rotation > 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0)));
	}
	else if (rotation > 90 && rotation < 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((rotation * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((rotation * M_PI) / 180.0)));
	}
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
