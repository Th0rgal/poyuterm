#include <SFML/Audio.hpp>
#include "views/music/music.hpp"

/**
 * Play Game music
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test sound 
 **/
void CAudio::startMusicGame(int musicType)
{
	switch(musicType)
	{
		case 0:
			musicInGame.openFromFile("music/bronze.wav");
			break;
		case 1:
			musicInGame.openFromFile("music/bach.wav");
			break;
		case 2:
			musicInGame.openFromFile("music/music.wav");
			break;
	}
    
    musicInGame.setLoop(true);
	musicInGame.play();

}

/**
 * pause the music
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test sound 
 **/
void CAudio::PausedMusicGame()
{
	musicInGame.pause();
}

/**
 * Play sound effect menu
 *
 * @author Valeran MAYTIE
 * @confidence 3 : impossible to test sound 
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
 * @confidence 3 : impossible to test sound 
 **/
void CAudio::easterEggsPlay()
{
	easterEggs.openFromFile("music/easterEggs.wav");
	easterEggs.play();
}