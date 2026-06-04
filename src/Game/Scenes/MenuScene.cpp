#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void MenuScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;
	bool buttonClicked = false;

	// entity instantiation
	Entity playButton = makeButton
	(
		sf::Vector2f
		(
			{
				window.getSize().x / 2.f,
				window.getSize().y / 2.f
			}
		),
		sf::Vector2f
		(
			{
				200.f,
				100.f
			}
		),
		Scene::PLAYING,
		"Play",
		font
	);

	// onstart systems
	setTextSystem(font); // font system is limited to one font
	setTextOriginSystem();
	setShapeOriginSystem();

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			if (const auto& mousePress = event->getIf<sf::Event::MouseButtonPressed>())
			{
				buttonClicked = true;
			}
		}

		// update systems
		buttonClickedSystem(sf::Vector2i(worldPos.x, worldPos.y), buttonClicked, dt);
		nextSceneSystem(window, font);

		window.clear();
		// render systems
		zIndexSystem(renderQueue);
		renderSystem(window, renderQueue);
		window.display();
	}
}