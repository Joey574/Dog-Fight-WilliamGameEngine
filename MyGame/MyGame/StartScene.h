#pragma once

#include "Engine/GameEngine.h"

class StartScene : public Scene
{
public:
	// Creates our Scene.
	StartScene();
private:

};

typedef std::shared_ptr<StartScene> StartScenePtr;