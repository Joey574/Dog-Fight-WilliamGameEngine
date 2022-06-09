#pragma once

#include "Engine/GameEngine.h"

class EndMessage : public GameObject
{
public:
	//Creates the EndMessage instance.
	EndMessage(int player_, float health1_, float health2_);

	// Functions overriden from GameObject:
	void draw();
	void update(sf::Time& elapsed);

private:
	sf::Text text_;
};

typedef std::shared_ptr<EndMessage> EndMessagePtr;

