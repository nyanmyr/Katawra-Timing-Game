#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

// TODO: rename scoreFeed to just feed
// TODO: add fail log to 'just feed'
// TODO: add sprites
// TODO: add sounds
// TODO: rename window
// TODO: make window and application logo
// TODO: publish

void PlayingScene(sf::RenderWindow& window, sf::Font& font, Difficulty difficulty) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;
	bool buttonClicked = false;

	float startingSpeed;
	float speedIncrease;
	float startSize;
	float minSize;
	float sizeDecrease;

	switch (difficulty)
	{
		case DIFFICULTY_HARD:
			startingSpeed = 130.f;
			speedIncrease = 30.f;

			startSize = 80.f;
			minSize = 15.f;
			sizeDecrease = 10.f;
			std::cout << "difficulty: HARD\n";
			break;
		case DIFFICULTY_NORMAL:
		default:
			startingSpeed = 100.f;
			speedIncrease = 12.5f;

			startSize = 100.f;
			minSize = 20.f;
			sizeDecrease = 5.f;
			std::cout << "difficulty: NORMAL\n";
			break;
	}

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
		startingSpeed,
		speedIncrease
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
		startSize, // start size
		minSize, // min size
		sizeDecrease // size decrease
	);

	Entity score = makeUIText
	(
		{
			25.f,
			25.f
		},
		font,
		"Test"
	);

	Entity cameraShake = makeCameraShake();
	Entity scoreFeed = makeScoreFeed();

	while (window.isOpen())
	{
		// in this case the extra baggage is afforable :p
		setTextSystem(font); // font system is limited to one font
		setTextOriginSystem();
		setShapeOriginSystem();

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
						font,
						indicator,
						hitbox,
						cameraShake,
						scoreFeed
					);
				}
			}
		}

		// update systems
		spawnHitbox
		(
			hitbox,
			slider,
			dt
		);
		moveIndicator_Update
		(
			indicator,
			slider,
			hitbox
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
			hitbox,
			dt
		);
		shakeCamera_UpdateSystem
		(
			cameraShake,
			window,
			dt
		);
		doScoreFeed
		(
			{
				window.getSize().x / 2.f,
				25.f
			},
			dt,
			scoreFeed
		);

		window.clear();
		// render systems
		zIndexSystem(renderQueue);
		renderSystem(window, renderQueue);
		window.display();
	}
}