#include "Background.h"

Background::Background()
{
	sprite_.setRotation(0);
	sprite_.setTexture(GAME.getTexture("Resources/background.png"));
	assignTag("Background");
}

void Background::draw()
{
	GAME.getRenderWindow().draw(sprite_);
}