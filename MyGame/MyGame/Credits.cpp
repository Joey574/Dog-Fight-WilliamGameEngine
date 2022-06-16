#include "Credits.h"
#include "StartMessage.h"
#include "GameScene.h"
#include <sstream>
#include <Windows.h>

const float SPEED = 0.1f;

Credits::Credits()
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(sf::Vector2f(440.0f, 700.0f));
	text_.setCharacterSize(48);
	text_.setFillColor(sf::Color::Red);

	std::stringstream stream;
	stream << "Two Mans Sky\n\nProgrammers\n\nEric Pace\nJoseph Soroka\n\nIdeas by\n\nEric Pace\n\nStolen by Joseph Soroka\n\nSound Design\n\nJoseph Soroka\nBrooks Sammarco\nSlater Swart\n\nSpecial Thanks\n\nMicheal T. Miyoshi\nJackson Heckert";

	text_.setString(stream.str());
}

void Credits::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void Credits::update(sf::Time& elapsed)
{
	float sElapsed = elapsed.asSeconds();
	float msElapsed = elapsed.asMilliseconds();

	timer_ -= sElapsed;
	sf::Vector2f pos;
	pos = text_.getPosition();
	pos.y -= (SPEED * msElapsed);
	text_.setPosition(pos.x, pos.y);
	if (timer_ <= 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		StartMessagePtr startMessage = std::make_shared<StartMessage>();
		GAME.getCurrentScene().addGameObject(startMessage);
		makeDead();
	}
}