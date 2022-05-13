#include "MeteorSpawner.h"

const int SPAWN_DELAY = 1000;

void MeteorSpawner::update(sf::Time& elapsed)
{
	int msElapsed = elapsed.asMilliseconds();
	timer_ -= msElapsed;

	if (timer_ <= 0)
	{
		timer_ = SPAWN_DELAY;

		sf::Vector2u size = GAME.getRenderWindow().getSize();

		float meteorX = (float)(size.x + 100);

		float meteorY = 50 + (float)(rand() % (size.y - 150));

		float speedV = (float)(rand() % 30) / 100;

		MeteorPtr meteor = std::make_shared<Meteor>(sf::Vector2f(meteorX, meteorY), speedV);
		GAME.getCurrentScene().addGameObject(meteor);
	}
}