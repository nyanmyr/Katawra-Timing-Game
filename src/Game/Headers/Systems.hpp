#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/NacreCoordinator.hpp"
#include "Components.hpp"

// oughta make some of these parameters as consts

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void setTextSystem(sf::Font& font);
void setTextOriginSystem();
void setShapeOriginSystem();

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
void buttonClickedSystem(sf::Vector2i& mouseVector, bool& buttonClicked, const DeltaTime dt);
void nextSceneSystem(sf::RenderWindow& window, sf::Font& font);

void Hit_Control
(
	Entity indicator,
	Entity hitbox
);
void moveIndicator_Update
(
	Entity indicator,
	Entity slider
);
void spawnHitbox
(
	Entity hitbox,
	Entity slider,
	DeltaTime dt
);

void indicatorSpeed
(
	Entity indicator,
	Entity hitbox
);

void moveSystem(const DeltaTime dt);
void dragSystem(const DeltaTime dt);

void displayScore
(
	Entity score,
	Entity hitbox
);

// make edge collision system here

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void zIndexSystem(std::queue<Entity>& renderQueue);
void renderSystem(sf::RenderWindow& window, std::queue<Entity>& renderQueue);

#endif
