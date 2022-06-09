#define _USE_MATH_DEFINES
#include "math.h"
#include "Pellet.h"

const float SPEED = 0.3f;

Pellet::Pellet(sf::Vector2f pos, int rot)
{
	sprite_.setTexture(GAME.getTexture("Resources/pellet.png"));
	sprite_.setPosition(pos);
	sprite_.setRotation(rot);
	assignTag("pellet");
}

void Pellet::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Pellet::update(sf::Time& elapsed)
{
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

sf::FloatRect Pellet::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Pellet::handleCollision(GameObject& otherGameObject)
{
	float dam = 0.5;

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

	if (!otherGameObject.hasTag("pellet"))
	{
		makeDead();
	}
}
