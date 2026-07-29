#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../../Engine/NacreCoordinator.hpp"
#include "Components.hpp"
#include "EntityMaker.hpp"

// oughta make some of these parameters as consts

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void getThemeBrightness
(
	float& themeBrightness,
	const sf::Color& themeColor
);
void adjustTextColor
(
	float themeBrightness,
	sf::Color& textColor
);
void loadSoundStatusData_Start(DSoundStatus& soundStatusData);
void loadThemeColorData_Start(DThemeColor& themeColorData);
void loadSavedScoresData_Start(DSavedScores& savedScoresData);
void adjustSoundTextureEnum_Start
(
	const DSoundStatus& soundStatusData,
	ETexture& soundTextureEnum
);
void adjustMusicTextureEnum_Start
(
	const DSoundStatus& soundStatusData,
	ETexture& musicTextureEnum
);
void setText_Start();
void setTextOrigin_Start();

void loadPlayingTextures_Start(Entity loadedTextures);
void loadMenuTextures_Start(Entity loadedTextures);
void loadSprites_Start(Entity loadedTextures);

void loadMenuSoundEffects_Start(Entity soundEffects);
void loadPlayingSoundEffects_Start(Entity soundEffects);

void loadPlayingMusicTrack(Entity musicTrack);
void loadMenuMusicTrack(Entity musicTrack);

void setSpriteOrigins_Start();

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
void updateSliderPointers_Update
(
	Entity redSliderPointer,
	Entity greenSliderPointer,
	Entity blueSliderPointer,
	sf::Color& themeColor
);

void resetColor_Update();
void resetTextColor_Update();

void saveSoundStatusData_Update
(
	DSoundStatus& soundStatusData,
	Entity soundButton,
	Entity musicButton
);
void saveThemeColorData_Update
(
	DThemeColor& themeColorData,
	const sf::Color themeColor
);
void easterEggKeyReleased
(
	std::queue<sf::Keyboard::Scancode>& easterEggKeys,
	std::queue<sf::Keyboard::Scancode>& enteredKeys,
	const sf::Event::KeyReleased* const keyReleased
);
void buttonClicks_Update
(
	Entity sceneTransition,
	sf::Vector2i mouseVector
);
void releaseButton_Update();
void doEasterEgg_Update
(
	std::queue<sf::Keyboard::Scancode>& easterEggKeys,
	std::queue<sf::Keyboard::Scancode>& enteredKeys,
	sf::Color& themeColor,
	sf::Color& textColor,
	float& themeBrightness
);
void scoreboard_Update
(
	bool& isSavedScoresModified,
	Entity scoreHeader,
	sf::Font& normalFont,
	sf::Color textColor,
	sf::Vector2f startPos,
	DSavedScores& savedScores,
	const Difficulty difficulty,
	std::vector<Entity>& scores
);
void doSoundControl_Update(Entity soundButton);
void changeSoundButtonTexture_Update(Entity loadedTextures);
void button_Update
(
	sf::Vector2i mouseVector,
	DeltaTime dt
);
void buttonFollowMouse_Update(sf::Vector2i mouseVector);
void doSceneTransition
(
	Entity sceneTransition,
	DeltaTime dt,
	const sf::RenderWindow& window
);
void nextSceneSaveSoundStatusData_Update
(
	DSoundStatus& soundStatusData,
	Entity soundButton,
	Entity musicButton
);
void nextSceneSaveThemeColorData_Update
(
	DThemeColor& themeColorData,
	const sf::Color themeColor
);
void doThemeColor_Update
(
	Entity redSliderPointer,
	Entity greenSliderPointer,
	Entity blueSliderPointer,
	sf::Color& themeColor,
	sf::Color& textColor,
	float& themeBrightness
);
void nextScene_Update
(
	Entity sceneTransition,
	sf::RenderWindow& window,
	sf::Font& normalFont,
	sf::Font& titleFont
);

void playIntro_Update
(
	Entity intro,
	Entity sceneTransition,
	DeltaTime dt
);

void hit_Control
(
	bool& isSavedScoresModified,
	float themeBrightness,
	sf::Font& font,
	Entity indicator,
	Entity hitbox,
	Entity cameraShake,
	Entity scoreFeed,
	Entity sceneTransition,
	const Difficulty difficulty,
	DSavedScores& savedScores
);
void moveIndicator_Update
(
	Entity indicator,
	Entity slider,
	Entity hitbox,
	Entity hum,
	Entity sceneTransition
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
	Entity hitbox,
	Entity sceneTransition
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
void playSounds_Update
(
	Entity soundEffects,
	Entity sceneTransition,
	Entity soundButton
);
void playMusic_Update
(
	Entity musicTrack,
	Entity sceneTransition,
	Entity musicButton,
	std::optional<sf::Music>& music
);
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
