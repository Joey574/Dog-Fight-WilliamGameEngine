#pragma once

#include "Engine/GameEngine.h"

class Credits : public GameObject
{
public:
	//Creates the Credits instance.
	Credits();

	// Functions overriden from GameObject:
	void draw();
	void update(sf::Time& elapsed);

private:
	sf::Text text_;
	int timer_ = 1;
};

typedef std::shared_ptr<Credits> CreditsPtr;
