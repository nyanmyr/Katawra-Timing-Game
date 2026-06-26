#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/NacreCoordinator.hpp"
#include "Components.hpp"
#include "EntityMaker.hpp"

// oughta make some of these parameters as consts

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void setTextSystem(sf::Font& font);
void setTextOriginSystem();

void loadTextures_StartSystem(Entity loadedTextures);
void loadSprites_StartSystem(Entity loadedTextures);

void loadSoundEffects_Start(Entity soundEffects);

void setSpriteOrigins_StartSystem();


// -------------------------------------------------------
// update systems
// -------------------------------------------------------
void buttonClicks_UpdateSystem(sf::Vector2i mouseVector);
void button_Update
(
	sf::Vector2i mouseVector,
	DeltaTime dt
);
void nextSceneSystem(sf::RenderWindow& window, sf::Font& font);

void Hit_Control
(
	sf::Font& font,
	Entity indicator,
	Entity hitbox,
	Entity cameraShake,
	Entity scoreFeed
);
void moveIndicator_Update
(
	Entity indicator,
	Entity slider,
	Entity hitbox
);
void spawnHitbox
(
	Entity hitbox,
	Entity slider,
	DeltaTime dt
);

void indicatorSpeed
(
	Entity slider,
	Entity indicator,
	Entity hitbox
);
void moveSystem(const DeltaTime dt);
void dragSystem(const DeltaTime dt);

void displayScore
(
	Entity score,
	Entity hitbox,
	DeltaTime dt
);
void displayHits
(
	Entity hits,
	Entity hitbox
);

void shakeCamera_UpdateSystem
(
	Entity cameraShake,
	sf::RenderWindow& window,
	DeltaTime dt
);
void doFeed
(
	sf::Vector2f startPos,
	DeltaTime dt,
	Entity feed
);
void playSounds(Entity soundEffects);
void delete_UpdateSystem(DeltaTime dt);

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void zIndexSystem(std::queue<Entity>& renderQueue);
void renderSystem(sf::RenderWindow& window, std::queue<Entity>& renderQueue);

#endif
