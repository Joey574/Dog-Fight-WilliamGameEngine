#pragma once

#include "Engine/GameEngine.h"

class StartMusic : public GameObject
{
public:

	StartMusic();

private:

	sf::Sound music_;

};

typedef std::shared_ptr<StartMusic> StartMusicPtr;
