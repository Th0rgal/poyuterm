#pragma once

#include <SFML/Audio.hpp>


class CAudio
{
	sf::Music musicInGame;
	sf::Music menuChange;


public:
	void startMusicGame();
	void PausedMusicGame();
	void menuChangePlay();
};