#include "Health1.h"
#include "GameScene.h"
#include <sstream>

Health1::Health1()
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(10, 5);
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Blue);
	assignTag("health1");
}

void Health1::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void Health1::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();

	std::stringstream stream;
	stream << "HP: " << scene.getHealth1();

	text_.setString(stream.str());
}