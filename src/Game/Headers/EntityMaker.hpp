#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"
#include "Components.hpp"

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str
);

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str,
	int size,
	sf::Color col
);

Entity makeLog
(
	sf::Vector2f pos,
	sf::Font& font,
	sf::Color col,
	std::string str,
	float timer,
	float fadeSet
);

Entity& makeButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
	std::string str,
	sf::Font& font,
	Scene scene
);

Entity& makeIndicator
(
	TextureEnum texture,
	sf::Vector2f pos,
	sf::Vector2f size,
	float speed,
	float speedIncrease
);

Entity& makeSlider
(
	TextureEnum texture,
	sf::Vector2f pos,
	sf::Vector2f size,
	sf::Vector2f slider
);

Entity& makeHitbox
(
	TextureEnum texture,
	Entity slider,
	float startSize,
	float minSize,
	float sizeDecrease
);

Entity& makeBackground
(
	TextureEnum texture,
	sf::Vector2f size
);

Entity makeCameraShake();
Entity makeFeed();
Entity makeLoadedTexturesContainer();
Entity makeSoundEffectsContainer();
Entity makeSound(SoundEffect type);
Entity makeSound(SoundEffect type, float pitch);

#endif