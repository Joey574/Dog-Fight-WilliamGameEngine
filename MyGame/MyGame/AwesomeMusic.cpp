#include "AwesomeMusic.h"

AwesomeMusic::AwesomeMusic()
{
	Music_.setBuffer(GAME.getSoundBuffer("Resources/Awesome Music.aif"));
	Music_.play();
}