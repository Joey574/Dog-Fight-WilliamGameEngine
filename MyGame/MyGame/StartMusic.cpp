#include "StartMusic.h"
#include "StartScene.h"
#include <iostream>

StartMusic::StartMusic()
{
	StartScene& scene = (StartScene&)GAME.getCurrentScene();

	music_.setLoop(true);
	music_.setBuffer(GAME.getSoundBuffer("Resources/30 second music clip.wav"));
	music_.play();
}