#include "Health2.h"
#include "GameScene.h"
#include <sstream>

Health2::Health2()
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(1150, 5);
	text_.setCharacterSize(24);
	text_.setFillColor(sf::Color::Red);
	assignTag("health2");
}

void Health2::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void Health2::update(sf::Time& elapsed)
{
	GameScene& scene = (GameScene&)GAME.getCurrentScene();
	std::stringstream stream;
	stream << "HP: " << scene.getHealth2();

	text_.setString(stream.str());
}