#include "EndMessage.h"
#include "GameScene.h"
#include "StartScene.h"
#include <sstream>
#include <iostream>

EndMessage::EndMessage(int player_, float health1_, float health2_)
{
	text_.setFont(GAME.getFont("Resources/Courneuf-Regular.ttf"));
	text_.setPosition(sf::Vector2f(50.0f, 50.0f));
	text_.setCharacterSize(48);
	text_.setFillColor(sf::Color::Red);


	std::stringstream stream;
	if (health1_ <= 0 && player_ == 1)
	{
		stream << "You Lose.\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	if (health1_ <= 0 && player_ == 2)
	{
		stream << "Player 2 Wins!\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	if (health2_ <= 0 && player_ == 1)
	{
		stream << "You Win!\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}
	if (health2_ <= 0 && player_ == 2)
	{
		stream << "Player 1 Wins!\nPress 1 to play again\nPress 2 to return to start.\nPress 3 to quit";
	}

	text_.setString(stream.str());

}

void EndMessage::draw()
{
	GAME.getRenderWindow().draw(text_);
}

void EndMessage::update(sf::Time& time, int player_)
{
	std::cout << "T1\n";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		std::cout << "T2\n";
		GameScenePtr scene = std::make_shared<GameScene>(player_);
		GAME.setScene(scene);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		std::cout << "T3\n";
		StartScenePtr start = std::make_shared<StartScene>();
		GAME.setScene(start);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		std::cout << "T4\n";
		exit(0);
	}
}