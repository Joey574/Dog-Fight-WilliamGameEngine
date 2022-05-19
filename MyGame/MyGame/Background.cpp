#include "Background.h"

Background::Background()
{
	sprite_.setRotation(0);
	//sprite_.setOrigin(sf::Vector2f());
	sprite_.setTexture(GAME.getTexture("Resources/background.png"));
	//sprite_.setPosition(sf::Vector2f(730, 530));
	assignTag("Background");
}

void Background::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}