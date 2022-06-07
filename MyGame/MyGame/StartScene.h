#pragma once

#include "Engine/GameEngine.h"

class StartScene : public Scene
{
public:
	// Creates our Scene.
	StartScene();

};

typedef std::shared_ptr<StartScene> StartScenePtr;