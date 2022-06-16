#include "StartMessage.h"
#include "GameScene.h"
#include "Credits.h"
#include <sstream>
#include <Windows.h>

StartMessage::StartMessage()
{
	Sleep(500);
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(sf::Vector2f(50.0f, 50.0f));
	text_.setCharacterSize(48);
	text_.setFillColor(sf::Color::Red);

	std::stringstream stream;
	stream << "1. Single Player \n\n2. Multiplayer Player\n\n3. Credits Player";

	text_.setString(stream.str());
}

void StartMessage::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void StartMessage::update(sf::Time& time)
{
	int player_;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		player_ = 1;
		GameScenePtr scene = std::make_shared<GameScene>(player_);
		GAME.setScene(scene);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		player_ = 2;
		GameScenePtr scene = std::make_shared<GameScene>(player_);
		GAME.setScene(scene);
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		CreditsPtr credits = std::make_shared<Credits>();
		GAME.getCurrentScene().addGameObject(credits);
		makeDead();
		return;
	}
}