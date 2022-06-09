#pragma once

#include "Engine/GameEngine.h"

class StartMessage : public GameObject
{
public:
	//Creates the StartMessage instance.
	StartMessage();

	// Functions overriden from GameObject:
	void draw();
	void update(sf::Time& elapsed);

private:
	sf::Text text_;
};

typedef std::shared_ptr<StartMessage> StartMessagePtr;