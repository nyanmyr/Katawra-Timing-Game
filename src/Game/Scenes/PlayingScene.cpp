#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void PlayingScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;

	// entity instantiation
	Entity player = makePlayer
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
				40.f,
				40.f
			}
		),
		sf::Vector2f
		(
			{
				-300.f,
				-300.f
			}
		),
		sf::Vector2f
		(
			{
				300.f,
				300.f
			}
		),
		sf::Vector2f
		(
			{
				500.f,
				500.f
			}
		),
		sf::Vector2f
		(
			{
				50.f,
				50.f
			}
		)
	);

	// onstart systems
	setTextSystem(font); // font system is limited to one font
	setTextOriginSystem();
	setShapeOriginSystem();

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}
		}

		// systems
		playerControlSystem(player, dt);
		moveSystem(dt);
		dragSystem(dt);

		window.clear();
		// render systems
		zIndexSystem(renderQueue);
		renderSystem(window, renderQueue);
		window.display();
	}
}