#include "Music.h"

Music::Music()
{
	music_.setLoop(true);
	music_.setBuffer(GAME.getSoundBuffer("Resources/30 second music clip.wav"));
	music_.play();
}