#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

// TODO: make movement slow as it nears the edge
// TODO: bonus score if hasn't hit the edge twice?

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
		100.f, // starting speed
		25.f // speed increase
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
		100.f, // start size
		10.f, // min size
		10.f // size decrease
	);

	Entity score = makeUIText
	(
		{
			25.f,
			25.f
		},
		font
	);


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
				if (buttonPress->scancode == sf::Keyboard::Scancode::Space)
				{
					Hit_Control
					(
						indicator,
						hitbox
					);
				}
			}
		}

		// update systems
		setShapeOriginSystem();
		spawnHitbox
		(
			hitbox,
			slider,
			dt
		);
		moveIndicator_Update
		(
			indicator,
			slider
		);
		indicatorSpeed
		(
			slider,
			indicator,
			hitbox
		);
		moveSystem(dt);
		displayScore
		(
			score,
			hitbox
		);

		window.clear();
		// render systems
		zIndexSystem(renderQueue);
		renderSystem(window, renderQueue);
		window.display();
	}
}