#include "Ammo.h"
#include "GameScene.h"
#include <sstream>

Ammo::Ammo(sf::Vector2f pos)
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(pos);
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::White);
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
	stream << "Ammo: " << scene.getAmmo();

	text_.setString(stream.str());
}