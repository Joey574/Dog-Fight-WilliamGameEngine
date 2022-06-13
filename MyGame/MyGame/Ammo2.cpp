#include "Ammo2.h"
#include "GameScene.h"
#include <sstream>

Ammo2::Ammo2()
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(1150, 25);
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Red);
	assignTag("ammo2");
}

void Ammo2::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void Ammo2::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "Ammo: " << scene.getAmmo2();

	text_.setString(stream.str());
}