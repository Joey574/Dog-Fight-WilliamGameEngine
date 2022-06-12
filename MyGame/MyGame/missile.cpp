#define _USE_MATH_DEFINES
#include "math.h"
#include "Missile.h"

const float SPEED = 0.5f;

Missile::Missile(sf::Vector2f pos, int rot, int ID)
{
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

	if (ID_ == 0)
	{
		Target = scene.getEnemyPos();
	}
	else if (ID_ == 1 || ID_ == 2)
	{
		Target = scene.getShipPos();
	}

	int msElapsed = elapsed.asMilliseconds();

	int rotation = sprite_.getRotation();

	sf::Vector2f pos = sprite_.getPosition();

	float x = pos.x;
	float y = pos.y;

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;

	if (pos.x > GAME.getRenderWindow().getSize().x || pos.y > GAME.getRenderWindow().getSize().y || pos.x < 0 || pos.y < 0)
	{
		makeDead();
	}

	if (Target.y < pos.y)
	{
		y -= SPEED * msElapsed;
		up = true;
	}
	if (Target.y > pos.y)
	{
		y += SPEED * msElapsed;
		down = true;
	}
	if (Target.x < pos.x)
	{
		x -= SPEED * msElapsed;
		left = true;
	}
	if (Target.x > pos.x)
	{
		x += SPEED * msElapsed;
		right = true;
	}

	rotationSet(up, down, left, right);
	sprite_.setPosition(x, y);
	/*if (rotation == 0 || rotation == 180)
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
	}*/
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

void Missile::rotationSet(bool up, bool down, bool left, bool right)
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
