#include "EndMessage.h"
#include "GameScene.h"
#include "StartScene.h"
#include <sstream>
#include <iostream>

EndMessage::EndMessage(int player_, float health1_, float health2_)
{
	player(player_);
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(sf::Vector2f(50.0f, 50.0f));
	text_.setCharacterSize(48);

	std::stringstream stream;

	if (health1_ <= 0 && health2_ <= 0)
	{
		text_.setFillColor(sf::Color::Green);
		stream << "A Tie.\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	else if (health1_ <= 0 && player_ == 1)
	{
		text_.setFillColor(sf::Color::Red);
		stream << "You Lose.\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	else if (health1_ <= 0 && player_ == 2)
	{
		text_.setFillColor(sf::Color::Red);
		stream << "Player 2 Wins!\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	else if (health2_ <= 0 && player_ == 1)
	{
		text_.setFillColor(sf::Color::Blue);
		stream << "You Win!\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	else if (health2_ <= 0 && player_ == 2)
	{
		text_.setFillColor(sf::Color::Blue);
		stream << "Player 1 Wins!\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}

	text_.setString(stream.str());

}

void EndMessage::player(int player_)
{
	playercount = player_;
}

void EndMessage::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void EndMessage::update(sf::Time& time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		GameScenePtr scene = std::make_shared<GameScene>(playercount);
		GAME.setScene(scene);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		StartScenePtr start = std::make_shared<StartScene>();
		GAME.setScene(start);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		exit(0);
	}
}