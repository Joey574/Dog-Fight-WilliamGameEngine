#pragma once

#include "Engine/GameEngine.h"

class Music : public GameObject
{
public:

	Music();

private:

	sf::Sound music_;

};

typedef std::shared_ptr<Music> MusicPtr;