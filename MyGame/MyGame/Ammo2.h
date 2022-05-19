#pragma once

#include "Engine/GameEngine.h"

class Ammo2 : public GameObject
{
public:
	// Creates the Ammo instance.
	Ammo2();

	// Functions overrid from GameObject:
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};

typedef std::shared_ptr<Ammo2> Ammo2Ptr;
