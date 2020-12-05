#pragma once

#include <SFML/Audio.hpp>


class CAudio
{
	sf::Music musicInGame;

public:
	void startMusicGame();
	void PausedMusicGame();
};