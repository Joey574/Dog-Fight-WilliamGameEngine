#include "Laser.h"

const float SPEED = 1.3f;

Laser::Laser(sf::Vector2f pos, int rot)
{
	sprite_.setTexture(GAME.getTexture("Resources/laser.png"));
	sprite_.setPosition(pos);
	sprite_.setRotation(rot);
	assignTag("laser");
}

void Laser::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Laser::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x > GAME.getRenderWindow().getSize().x || pos.y > GAME.getRenderWindow().getSize().y || pos.x < 0 || pos.y < 0)
	{
		makeDead();
	}
	else if (sprite_.getRotation() == 0)
	{
		sprite_.setPosition(sf::Vector2f(pos.x + SPEED * msElapsed, pos.y));
	}
	else if (sprite_.getRotation() == 45)
	{
		sprite_.setPosition(sf::Vector2f((pos.x + ((SPEED * msElapsed) / 2.0f)), pos.y + ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 90)
	{
		sprite_.setPosition(sf::Vector2f(pos.x, pos.y + SPEED * msElapsed));
	}
	else if (sprite_.getRotation() == 135)
	{
		sprite_.setPosition(sf::Vector2f((pos.x - ((SPEED * msElapsed) / 2.0f)), pos.y + ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 180)
	{
		sprite_.setPosition(sf::Vector2f(pos.x - SPEED * msElapsed, pos.y));
	}
	else if (sprite_.getRotation() == 225)
	{
		sprite_.setPosition(sf::Vector2f((pos.x - ((SPEED * msElapsed) / 2.0f)), pos.y - ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x, pos.y - SPEED * msElapsed));
	}
	else if (sprite_.getRotation() == 315)
	{
		sprite_.setPosition(sf::Vector2f((pos.x + ((SPEED * msElapsed) / 2.0f)), pos.y - ((SPEED * msElapsed)) / 2.0f));
	}
}

sf::FloatRect Laser::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Laser::handleCollision(GameObject& otherGameObject)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	sf::Vector2f pos = sprite_.getPosition();

	ExplosionPtr explosion = std::make_shared<Explosion>(sprite_.getPosition());

	if (otherGameObject.hasTag("ship"))
	{
		GAME.getCurrentScene().addGameObject(explosion);
		scene.decreaseHealth1();
	}

	if (otherGameObject.hasTag("enemy"))
	{
		GAME.getCurrentScene().addGameObject(explosion);
		scene.decreaseHealth2();
	}

	makeDead();
}

