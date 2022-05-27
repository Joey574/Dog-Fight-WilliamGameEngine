#include "Music.h"

Music::Music()
{
	music_.setLoop(true);
	music_.setBuffer(GAME.getSoundBuffer("Resources/Awesome Music.wav"));
	music_.play();
}