#pragma once

#include "Engine/GameEngine.h"
#include "Buff.h"

class BuffSpawner : public GameObject
{
public:
	void update(sf::Time& elapsed);
private:
	double timer_ = 0;
};

typedef std::shared_ptr<BuffSpawner> BuffSpawnerPtr;
