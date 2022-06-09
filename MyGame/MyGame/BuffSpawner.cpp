#include "BuffSpawner.h"


const int SPAWN_DELAY = 5;

void BuffSpawner::update(sf::Time& elapsed)
{

	double sElapsed = elapsed.asSeconds();
	timer_ -= sElapsed;

	if (timer_ <= 0)
	{
		timer_ = SPAWN_DELAY;

		BuffPtr buff = std::make_shared<Buff>();
		GAME.getCurrentScene().addGameObject(buff);
	}
}