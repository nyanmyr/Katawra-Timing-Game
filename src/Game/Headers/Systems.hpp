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
void setText_Start(sf::Font& font);
void setTextOrigin_Start();

void loadPlayingTextures_Start(Entity loadedTextures);
void loadMenuTextures_Start(Entity loadedTextures);
void loadSprites_Start(Entity loadedTextures);

void loadMenuSoundEffects_Start(Entity soundEffects);
void loadPlayingSoundEffects_Start(Entity soundEffects);

void setSpriteOrigins_Start();

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
void buttonClicks_Update(sf::Vector2i mouseVector);
void button_Update
(
	sf::Vector2i mouseVector,
	DeltaTime dt
);
void doSceneTransition
(
	Entity sceneTransition,
	DeltaTime dt,
	const sf::RenderWindow& window
);
void nextScene_Update(sf::RenderWindow& window, sf::Font& font);

void playIntro_Update
(
	Entity intro,
	DeltaTime dt
);

void hit_Control
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
	Entity hitbox,
	Entity hum
);
void spawnHitbox_Update
(
	Entity hitbox,
	Entity slider,
	DeltaTime dt
);

void adjustIndicatorSpeed_Update
(
	Entity slider,
	Entity indicator,
	Entity hitbox
);
void move_Update(const DeltaTime dt);
void drag_Update(const DeltaTime dt);

void displayScore_Update
(
	Entity score,
	Entity hitbox,
	DeltaTime dt
);
void displayHits_Update
(
	Entity hits,
	Entity hitbox
);

void shakeCamera_Update
(
	Entity cameraShake,
	sf::RenderWindow& window,
	DeltaTime dt
);
void doFeed_Update
(
	sf::Vector2f startPos,
	DeltaTime dt,
	Entity feed
);
void playSounds_Update(Entity soundEffects);
void delete_Update(DeltaTime dt);


// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void zIndex_Render(std::queue<Entity>& renderQueue);
void renderSceneTransition
(
	sf::RenderWindow& window,
	Entity sceneTransition
);
void render(sf::RenderWindow& window, std::queue<Entity>& renderQueue);

#endif
