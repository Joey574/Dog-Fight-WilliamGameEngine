#pragma once

#include "Engine/GameEngine.h"

class EndScene : public Scene
{
public:
	// Creates our Scene.
	EndScene(int player_, float health1_, float health2_);

};

typedef std::shared_ptr<EndScene> EndScenePtr;
