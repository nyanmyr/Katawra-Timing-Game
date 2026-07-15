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
	Entity sound;

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
	bool clear = false;
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
	INDICATOR_TEXTURE,
	FILL_TEXTURE,
	BACKGROUND_TEXTURE,
	BUTTON_TEXTURE,
	INNER_TEXTURE,
	OUTER_TEXTURE,
	TEXTURE_PLACEHOLDER_PLACEHOLDER,
	BUTTON_MUSIC_1_TEXTURE,
	BUTTON_MUSIC_2_TEXTURE,
	BUTTON_MUSIC_3_TEXTURE,
	BUTTON_MUSIC_OFF_TEXTURE,
	BUTTON_SOUND_1_TEXTURE,
	BUTTON_SOUND_2_TEXTURE,
	BUTTON_SOUND_3_TEXTURE,
	BUTTON_SOUND_OFF_TEXTURE,
	BUTTON_RETURN_TEXTURE
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
	BONUS_SOUND_EFFECT,
	BUTTON_SOUND_EFFECT,
	CENTER_SOUND_EFFECT,
	FAIL_SOUND_EFFECT,
	HIT_SOUND_EFFECT,
	HOVER_SOUND_EFFECT,
	UNHOVER_SOUND_EFFECT,
	BLIP1_SOUND_EFFECT,
	BLIP2_SOUND_EFFECT,
	BOUNCE_SOUND_EFFECT,
	HUM_SOUND_EFFECT
};

struct CSoundEffectsContainer
{
	std::unordered_map<SoundEffect, sf::SoundBuffer> sounds;
};

struct CSound
{
	SoundEffect type;
	std::optional<sf::Sound> sound;
	bool played = false;
	bool loop = false;
	float pitch = 1.f;
	float volume = 100.f;

	CSound() = default;
	CSound(SoundEffect type) :
		type(type) {
	};

	CSound(SoundEffect type, float pitch) :
		type(type), pitch(pitch) {
	};

	CSound(SoundEffect type, bool loop, float volume) :
		type(type), loop(loop), volume(volume) {
	};
};

struct CButtonSounds
{
	bool hovering = false, hovered = false, unhovered = false, clicked = false;
};

struct CDelete
{
	float timer = 0.f;
};

struct CIntro
{
	std::queue<Entity> texts;
	std::queue<std::pair<float, float>> timers;
	std::queue<SoundEffect> soundEffects;
};

struct CDoSpriteCenter
{ };

enum Music
{
	_8_BIT_ARCADE,
	_8_BIT_BEGINNING
};

enum FadeStatus
{
	FADING_IN,
	FADING_OUT,
	FADING_COMPLETED
};

struct CMusic
{
	Music type;
};

struct CMusicTrack
{
	bool hasCurrent = false;
	Entity current;
	std::queue<Music> track;
};

struct CSceneTransition
{
	bool active = true;
	float timer = 0.f;
	float fadeinTimer = 0.f;
	float fadeoutTimer = 0.f;
	FadeStatus status = FADING_IN;
	sf::RectangleShape box;

	// timer is set to fade in because it is expected that the entity is created at the start
	// i.e. the fade in cue of the scene transition
	CSceneTransition() = default;
	CSceneTransition(float fadeinTimer, float fadeoutTimer) :
		timer(fadeinTimer), fadeinTimer(fadeinTimer), fadeoutTimer(fadeoutTimer) {};
};

enum ESoundStatus
{
	QUARTER_SOUND,
	HALF_SOUND,
	FULL_SOUND,
	MUTED_SOUND
};

struct CSoundControl
{
	ESoundStatus current = ESoundStatus::FULL_SOUND;
};

struct CSoundStatusTextures
{
	std::unordered_map<ESoundStatus, TextureEnum> map;
};

struct DSoundStatus
{
	ESoundStatus soundStatus = ESoundStatus::FULL_SOUND;
	ESoundStatus musicStatus = ESoundStatus::FULL_SOUND;
};

#endif