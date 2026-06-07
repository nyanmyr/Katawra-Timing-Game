#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

// TODO: make movement slow as it nears the edge

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
	Entity indicator = makeIndicator
	(
		
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{
			10.f,
			20.f
		},
		100 // starting speed
	);

	Entity slider = makeSlider
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{ // xbounds is tied to size
			window.getSize().x / 2.f,
			20.f
		},
		{ // slider min/ max
			0.f,
			100.f
		}
	);

	Entity hitbox = makeHitbox
	(
		slider,
		100.f,
		0
	);

	float tempX = window.getSize().x / 2.f;

	std::cout << "boundX min: " << tempX - (tempX / 2.f) << "\n";
	std::cout << "boundX max: " << tempX + (tempX / 2.f) << "\n\n";


	// onstart systems
	setTextSystem(font); // font system is limited to one font
	setTextOriginSystem();

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

			if (const auto& buttonPress = event->getIf<sf::Event::KeyReleased>())
			{

			}
		}

		// update systems
		setShapeOriginSystem();
		spawnHitbox
		(
			hitbox,
			slider
		);
		moveIndicator_Update
		(
			indicator,
			slider
		);

		moveSystem(dt);

		window.clear();
		// render systems
		zIndexSystem(renderQueue);
		renderSystem(window, renderQueue);
		window.display();
	}
}