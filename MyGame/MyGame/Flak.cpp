#define _USE_MATH_DEFINES
#include "Flak.h"
#include <math.h>

const float SPEED = 1.3f;

Flak::Flak(sf::Vector2f pos, int rot)
{
	sprite_.setTexture(GAME.getTexture("Resources/laser.png"));
	sprite_.setPosition(pos);
	sprite_.setRotation(rot);
	assignTag("flak");
}

void Flak::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}

void Flak::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();
	sf::Vector2f pos = sprite_.getPosition();

	if (pos.x > GAME.getRenderWindow().getSize().x || pos.y > GAME.getRenderWindow().getSize().y || pos.x < 0 || pos.y < 0)
	{
		makeDead();
	}
	else if (sprite_.getRotation() == 350)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 355)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 0)
	{
		sprite_.setPosition(sf::Vector2f(pos.x + SPEED * msElapsed, pos.y));
	}
	else if (sprite_.getRotation() == 5)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 10)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	/////////////
	else if (sprite_.getRotation() == 35)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 40)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 45)
	{
		sprite_.setPosition(sf::Vector2f((pos.x + ((SPEED * msElapsed) / 2.0f)), pos.y + ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 50)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 55)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	//////////////
	else if (sprite_.getRotation() == 80)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += SPEED * acos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= SPEED * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 85)
	{
		sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 90)
	{
		sprite_.setPosition(sf::Vector2f(pos.x, pos.y + SPEED * msElapsed));
	}
	else if (sprite_.getRotation() == 95)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 100)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	//////////////
	else if (sprite_.getRotation() == 125)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 130)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 135)
	{
		sprite_.setPosition(sf::Vector2f((pos.x - ((SPEED * msElapsed) / 2.0f)), pos.y + ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 140)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 145)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	///////////////
	else if (sprite_.getRotation() == 170)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 175)
	{
		sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y -= (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 180)
	{
		sprite_.setPosition(sf::Vector2f(pos.x - SPEED * msElapsed, pos.y));
	}
	else if (sprite_.getRotation() == 185)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 190)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	///////////
	else if (sprite_.getRotation() == 215)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 220)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 225)
	{
		sprite_.setPosition(sf::Vector2f((pos.x - ((SPEED * msElapsed) / 2.0f)), pos.y - ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 230)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 235)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	////////////
	else if (sprite_.getRotation() == 260)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 265)
	{
	sprite_.setPosition(sf::Vector2f(pos.x -= (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 270)
	{
		sprite_.setPosition(sf::Vector2f(pos.x, pos.y - SPEED * msElapsed));
	}
	else if (sprite_.getRotation() == 275)
	{
	sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 280)
	{
	sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	////////
	else if (sprite_.getRotation() == 305)
	{
	sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 310)
	{
	sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 315)
	{
		sprite_.setPosition(sf::Vector2f((pos.x + ((SPEED * msElapsed) / 2.0f)), pos.y - ((SPEED * msElapsed)) / 2.0f));
	}
	else if (sprite_.getRotation() == 320)
	{
	sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
	else if (sprite_.getRotation() == 325)
	{
	sprite_.setPosition(sf::Vector2f(pos.x += (SPEED * msElapsed) * cos((sprite_.getRotation() * M_PI) / 180.0), pos.y += (SPEED * msElapsed) * sin((sprite_.getRotation() * M_PI) / 180.0)));
	}
}

sf::FloatRect Flak::getCollisionRect()
{
	return sprite_.getGlobalBounds();
}

void Flak::handleCollision(GameObject& otherGameObject)
{
	float dam = 0.5;

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
