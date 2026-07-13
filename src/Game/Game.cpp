#include <SFML/Graphics.hpp>

#include "Headers/GameManager.hpp"
#include "Headers/Scenes.hpp"

#include <iostream>

using sf::RenderWindow;
using sf::VideoMode;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int MAX_FPS = 60;

const std::string FONT_FILEPATH = RESOURCES_PATH "arial.ttf";

void main() {
	RenderWindow window(VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Katawra Timing Game", sf::Style::Close); // change of the window here
	window.setFramerateLimit(MAX_FPS);
	sf::Image icon(SPRITES_PATH "favicon_icon.png");
	window.setIcon(icon);

	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// components registration
	nc.registerComponent<CPosition>();
	nc.registerComponent<CTransform>();
	nc.registerComponent<COrigin>();
	nc.registerComponent<CButton>();
	nc.registerComponent<CText>();
	nc.registerComponent<CNextScene>();
	nc.registerComponent<CZIndex>();
	nc.registerComponent<CVelocity>();
	nc.registerComponent<CSpeed>();
	nc.registerComponent<CSpeedIncrease>();
	nc.registerComponent<CPlayerController>();
	nc.registerComponent<CDrag>();
	nc.registerComponent<CXBounds>();
	nc.registerComponent<CHitbox>();
	nc.registerComponent<CScore>();
	nc.registerComponent<CMode>();
	nc.registerComponent<CCameraShake>();
	nc.registerComponent<CFeed>();
	nc.registerComponent<CLog>();
	nc.registerComponent<CSprite>();
	nc.registerComponent<CTexture>();
	nc.registerComponent<CTexturesContainer>();
	nc.registerComponent<SoundEffect>();
	nc.registerComponent<CSoundEffectsContainer>();
	nc.registerComponent<CSound>();
	nc.registerComponent<CButtonSounds>();
	nc.registerComponent<CDelete>();
	nc.registerComponent<CIntro>();
	nc.registerComponent<CDoSpriteCenter>();
	nc.registerComponent<CMusic>();
	nc.registerComponent<CMusicTrack>();
	nc.registerComponent<CSceneTransition>();
	nc.registerComponent<CSoundControl>();

	sf::Font font;
	if (!font.openFromFile(FONT_FILEPATH))
	{
		throw std::runtime_error("Font not found.");
	}

	playScene(window, Scene::MENU, font, Difficulty::DIFFICULTY_NORMAL);
}