#include <SFML/Audio.hpp>
#include "views/music/music.hpp"

/**
 * Play Game music
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test display
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
 * @confidence 3 : impossible to test display
 **/
void CAudio::PausedMusicGame()
{
	musicInGame.pause();
}

/**
 * Play sound effect menu
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test display
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
 * @confidence 3 : impossible to test display 
 **/
void CAudio::easterEggsPlay()
{
	easterEggs.openFromFile("music/easterEggs.wav");
	easterEggs.play();
}