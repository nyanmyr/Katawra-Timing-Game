#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"
#include "Components.hpp"

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str,
	int size,
	sf::Color col
);

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str,
	int size,
	sf::Color col,
	bool visible
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

Entity& makeTextButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
	std::string str,
	sf::Font& font,
	Scene scene,
	sf::Color col,
	sf::Color textCol
);

Entity& makeButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
	Scene scene,
	sf::Color col
);
Entity& makeButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
	sf::Color col
);
Entity& makeSoundButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
	std::unordered_map<ESoundStatus, TextureEnum> map,
	ESoundStatus status,
	sf::Color col
);

Entity& makeIndicator
(
	TextureEnum texture,
	sf::Vector2f pos,
	sf::Vector2f size,
	float speed,
	float speedIncrease
);

Entity& makeInnerBar
(
	TextureEnum texture,
	sf::Vector2f pos,
	sf::Vector2f size
);

Entity& makeObject
(
	TextureEnum texture,
	sf::Vector2f pos,
	sf::Vector2f size,
	int index
);

Entity& makeHitbox
(
	TextureEnum texture,
	Entity slider,
	float startSize,
	float minSize,
	float sizeDecrease,
	sf::Color col
);

Entity& makeBackground
(
	TextureEnum texture,
	sf::Vector2f size,
	sf::Color col
);

Entity makeCameraShake();
Entity makeFeed();
Entity makeLoadedTexturesContainer();

Entity makeSoundEffectsContainer();
Entity makeSound(SoundEffect type);
Entity makeSound(SoundEffect type, float pitch);
Entity makeLoopSound(SoundEffect type, float volume);

Entity makeMusic(Music type);
Entity makeMusicTrack();

Entity makeIntro
(
	const std::vector<Entity>& texts,
	const std::vector<float>& timers,
	const std::vector<SoundEffect>& soundEffects
);
Entity makeSceneTransition
(
	float fadeinTimer,
	float fadeoutTimer
);

#endif