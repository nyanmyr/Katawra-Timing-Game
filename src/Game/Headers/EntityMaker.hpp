#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"

// could prolly use some Vector2fs
Entity& makeButton(sf::Vector2f pos, sf::Vector2f size, Scene scene, std::string str, sf::Font& font);

Entity& makeMoving
(
	sf::Vector2f pos,
	sf::Vector2f size,
	sf::Vector2f xBounds,
	float speed
);

#endif