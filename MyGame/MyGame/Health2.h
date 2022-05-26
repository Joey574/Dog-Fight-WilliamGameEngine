#pragma once

#include "Engine/GameEngine.h"

class Health2 : public GameObject
{
public:
	// Creates the Health instance.
	Health2();

	// Functions overrid from GameObject:
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};

typedef std::shared_ptr<Health2>Health2Ptr;
