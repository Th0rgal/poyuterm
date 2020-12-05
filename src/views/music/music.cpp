#include <SFML/Audio.hpp>
#include "views/music/music.hpp"

/**
 * Play Game music
 *
 * @author Valeran MAYTIE
 **/
void CAudio::startMusicGame()
{
	musicInGame.openFromFile("music/music.wav");
    musicInGame.setLoop(true);
	musicInGame.play();

}

/**
 * pause the music
 *
 * @author Valeran MAYTIE
 **/
void CAudio::PausedMusicGame()
{
	musicInGame.pause();
}

/**
 * Play sound effect menu
 *
 * @author Valeran MAYTIE
 **/
void CAudio::menuChangePlay()
{
	menuChange.openFromFile("music/menuChange.wav");
	menuChange.play();
}

/**
 * Play Easter Egg music
 *
 * @author Valeran MAYTIE
 **/
void CAudio::easterEggsPlay()
{
	easterEggs.openFromFile("music/easterEggs.wav");
	easterEggs.play();
}