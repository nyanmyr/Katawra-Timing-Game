#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"

// could prolly use some Vector2fs
Entity& makePlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f minVelocity, sf::Vector2f maxVelocity, sf::Vector2f speed, sf::Vector2f drag);
Entity& makeButton(sf::Vector2f pos, sf::Vector2f size, Scene scene, std::string str, sf::Font& font);

#endif