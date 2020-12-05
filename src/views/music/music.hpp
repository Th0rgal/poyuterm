#pragma once

#include <SFML/Audio.hpp>


class CAudio
{
	sf::Music musicInGame;
	sf::Music menuChange;
	sf::Music easterEggs;
	sf::Music comboMusic;


public:
	void startMusicGame(int musicType);
	void PausedMusicGame();
	void menuChangePlay();
	void comboPlay();
	void easterEggsPlay();
};