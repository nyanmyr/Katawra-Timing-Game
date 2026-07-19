#ifndef SCENES_HPP
#define SCENES_HPP

#include <SFML/Graphics.hpp>

#include <stdexcept>

enum Scene {
	MENU,
	PLAYING
};

enum Difficulty
{
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

void playScene
(
	sf::RenderWindow& window,
	Scene scene,
	sf::Font& normalFont,
	sf::Font& titleFont,
	Difficulty difficulty
);
void menuScene
(
	sf::RenderWindow& window,
	sf::Font& normalFont,
	sf::Font& titleFont
);
void playingScene
(
	sf::RenderWindow& window,
	sf::Font& normalFont,
	sf::Font& titleFont,
	Difficulty difficulty
);


#endif