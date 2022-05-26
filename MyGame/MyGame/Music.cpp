#include "Music.h"

Music::Music()
{
	music_.setBuffer(GAME.getSoundBuffer("Resources/Awesome Music.aif"));
	music_.play();
}