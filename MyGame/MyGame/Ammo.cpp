#include "Ammo.h"
#include "GameScene.h"
#include <sstream>

Ammo::Ammo()
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(10, 5);
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Blue);
	assignTag("ammo");
}

void Ammo::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void Ammo::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "Ammo: " << scene.getAmmo1();

	text_.setString(stream.str());
}