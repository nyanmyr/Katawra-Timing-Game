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
	sf::Font& font,
	Difficulty difficulty
);
void MenuScene(sf::RenderWindow& window, sf::Font& font);
void PlayingScene
(
	sf::RenderWindow& window,
	sf::Font& font,
	Difficulty difficulty
);


#endif