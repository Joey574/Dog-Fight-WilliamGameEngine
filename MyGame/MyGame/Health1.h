#pragma once

#include "Engine/GameEngine.h"

class Health1 : public GameObject
{
public:
	// Creates the Health instance.
	Health1();

	// Functions overrid from GameObject:
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};

typedef std::shared_ptr<Health1>Health1Ptr;