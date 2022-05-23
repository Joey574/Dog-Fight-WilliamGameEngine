#pragma once

#include "Engine//GameEngine.h"

class AI : public GameObject
{
public:

	AI();

	void draw();
	void update(sf::Time& elapsed);
	sf::FloatRect getCollisionRect();

private:
	sf::Sprite sprite_;
	int fireTimer_ = 0;
};

typedef std::shared_ptr<AI> AIPtr;