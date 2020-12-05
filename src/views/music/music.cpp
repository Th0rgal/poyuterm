#include <SFML/Audio.hpp>
#include "views/music/music.hpp"


void CAudio::startMusicGame()
{
	musicInGame.openFromFile("music/music.wav");
    musicInGame.setLoop(true);
	musicInGame.play();

}

void CAudio::PausedMusicGame()
{
	musicInGame.pause();
}