#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scenes.hpp"
#include <optional>
#include <string>
#include <queue>

enum TextFormat
{
	TOP,
	MIDDLE,
	BOTTOM
};

struct CPosition
{
	float x, y;
};

struct CTransform
{
	float width = 0.f, height = 0.f;
	CTransform() = default;
	CTransform(const float width, const float height) :
		width(width), height(height) {
	};
};

struct COrigin
{
	float offsetX = 0.f, offsetY = 0.f;
	COrigin() = default;
	COrigin(const float offsetX, const float offsetY) :
		offsetX(offsetX), offsetY(offsetY) {};
};

struct CButton
{
	float clickedDuration, clickedTimer = 0.f;
	bool clicked = false, enabled = true;

	CButton() = default;
	CButton(const float clickedDuration, const bool enabled) :
		clickedDuration(clickedDuration), enabled(enabled) {};
};

struct CText
{
	std::optional<sf::Text> box;
	std::string string = " ";
	int size = 12;
	sf::Color color;
	TextFormat format;

	CText() = default;
	CText(sf::Text box, std::string string, int size, sf::Color color, TextFormat format) :
		box(box), string(string), size(size), color(color), format(format) {};
};

struct CNextScene
{
	Scene next;
	bool active;
};

struct CZIndex
{
	int index = true;
	bool visible = true;

	CZIndex() = default;
	CZIndex(int index, bool visible) :
		index(index), visible(visible) {
	};
};

struct CVelocity
{
	float x = 0.f, y = 0.f;
};

struct CSpeed
{
	float amount = 0.f, original = 0.f;

	CSpeed() = default;
	CSpeed(float amount) :
		amount(amount), original(amount) {
	};
};

struct CSpeedIncrease
{
	float increase = 0.f;
};

struct CPlayerController
{
	bool enabled = false;
};

struct CDrag
{
	float x = 0.f, y = 0.f;

	CDrag() = default;
	CDrag(float x, float y) :
		x(x), y(y) {
	};
};

struct CXBounds
{
	float min = 0.f, max = 0.f;
};

struct CHitbox
{
	Entity slider;
	float startSize = 0.f, minSize = 0.f, sizeDecrease = 0.f;
	bool spawned = false;
};

struct CScore
{
	int count = 0;
	int hits = 0;
	int bounces = 0;
	int unaccounted = 0;
	float fillTimer = 0.f;
};

enum GameMode
{
	MODE_NORMAL,
	MODE_HARD
};

struct CMode
{
	GameMode selected;
};

struct CCameraShake
{
	float intensity = 0.f;
	float timer = 0.f;
};

struct CFeed
{
	std::queue<Entity> feed;
	bool positionsSet = false;
};

struct CLog
{
	float timer = 0.f;
	float fadeSet = 0.f;
	float fadeTimer = 0.f;
};

struct CSprite
{
	std::optional<sf::Sprite> body;
};

// might reorganize this later
enum TextureEnum
{
	INDICATOR,
	BAR,
	FILL,
	BACKGROUND,
	TEXTURE_PLACEHOLDER_PLACEHOLDER
};

struct CTexture
{
	TextureEnum data;

	CTexture() = default;
	CTexture(TextureEnum texture) :
		data(texture) {
	};
};

struct CTexturesContainer
{
	std::unordered_map<TextureEnum, sf::Texture> map;
};

enum SoundEffect
{
	BONUS,
	BUTTON,
	CENTER,
	FAIL,
	HIT,
	HOVER
};

struct CSoundEffectsContainer
{
	std::unordered_map<SoundEffect, sf::SoundBuffer> sounds;
};

struct CSound
{
	SoundEffect type{};
	std::optional<sf::Sound> sound;
	bool played = false;
	float pitch = 1.f;

	CSound() = default;
	CSound(SoundEffect type) :
		type(type) {
	};

	CSound(SoundEffect type, float pitch) :
		type(type), pitch(pitch) {
	};
};

struct CDelete
{
	float timer = 0.f;
};

#endif