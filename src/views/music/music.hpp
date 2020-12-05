#pragma once

#include <SFML/Audio.hpp>


class CAudio
{
	sf::Music musicInGame;
	sf::Music menuChange;
	sf::Music easterEggs;


public:
	void startMusicGame();
	void PausedMusicGame();
	void menuChangePlay();
	void easterEggsPlay();
};