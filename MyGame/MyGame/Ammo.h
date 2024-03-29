#pragma once

#include "Engine/GameEngine.h"

class Ammo : public GameObject
{
public:
	// Creates the Ammo instance.
	Ammo();

	// Functions overrid from GameObject:
	void draw();
	void update(sf::Time& elapsed);
private:
	sf::Text text_;
};

typedef std::shared_ptr<Ammo> AmmoPtr;
