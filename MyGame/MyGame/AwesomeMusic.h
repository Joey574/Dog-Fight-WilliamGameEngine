#pragma once

#include "Engine//GameEngine.h"

class AwesomeMusic : public GameObject
{
public:
	AwesomeMusic();


private:

	sf::Sound Music_;
};

typedef std::shared_ptr<AwesomeMusic> AwesomeMusicPtr;