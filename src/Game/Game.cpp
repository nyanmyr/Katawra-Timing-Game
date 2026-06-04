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
	RenderWindow window(VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Nacre Engine", sf::Style::Close); // change of the window here
	window.setFramerateLimit(MAX_FPS);

	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// components registration
	nc.registerComponent<CPosition>();
	nc.registerComponent<CShape>();
	nc.registerComponent<CTransform>();
	nc.registerComponent<COrigin>();
	nc.registerComponent<CButton>();
	nc.registerComponent<CText>();
	nc.registerComponent<CNextScene>();
	nc.registerComponent<CZIndex>();
	nc.registerComponent<CVelocity>();
	nc.registerComponent<CSpeed>();
	nc.registerComponent<CPlayerController>();
	nc.registerComponent<CDrag>();

	sf::Font font;
	if (!font.openFromFile(FONT_FILEPATH))
	{
		throw std::runtime_error("Font not found.");
	}

	playScene(window, Scene::MENU, font);
}