#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"

// could prolly use some Vector2fs
Entity& makeButton(sf::Vector2f pos, sf::Vector2f size, Scene scene, std::string str, sf::Font& font);

Entity& makeIndicator
(
	sf::Vector2f pos,
	sf::Vector2f size,
	float speed
);

Entity& makeSlider
(
	sf::Vector2f pos,
	sf::Vector2f size,
	sf::Vector2f slider
);

Entity& makeHitbox
(
	Entity slider,
	float startSize,
	float minSize
);

#endif