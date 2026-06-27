#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

// TODO: time it right intro (with sounds)
// FIX: button and hover sound is unused
// TODO: seperate fill bar and content?
// TODO: add bounce on corners effect
// TODO: move indicator to point at the midpoint
// TODO: dark mode
// TODO: add background music
// TODO: make window and application logo
// TODO: bug fixing
// FIX: rename makers to correspond to sprite names
// FIX: make a seperate load texture for menu scene
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
		TextureEnum::INDICATOR,
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
		TextureEnum::BAR,
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
		TextureEnum::FILL,
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
		"Score: "
	);

	Entity hits = makeUIText
	(
		{
			25.f,
			75.f
		},
		font,
		"Hits: "
	);

	Entity cameraShake = makeCameraShake();
	Entity feed = makeFeed();
	Entity loadedTextures = makeLoadedTexturesContainer();
	Entity soundEffects = makeSoundEffectsContainer();
	Entity background = makeBackground
	(
		TextureEnum::BACKGROUND,
		{
			window.getDefaultView().getSize().x,
			window.getDefaultView().getSize().y
		}
	);

	loadTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);
	loadSoundEffects_Start(soundEffects);

	while (window.isOpen())
	{
		// in this case the extra baggage is afforable :p
		setText_Start(font); // font system is limited to one font
		setTextOrigin_Start();

		setSpriteOrigins_Start();

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
					hit_Control
					(
						font,
						indicator,
						hitbox,
						cameraShake,
						feed
					);
				}
			}
		}

		// update systems
		spawnHitbox_Update
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
		adjustIndicatorSpeed_Update
		(
			slider,
			indicator,
			hitbox
		);
		move_Update(dt);
		displayScore_Update
		(
			score,
			hitbox,
			dt
		);
		displayHits_Update
		(
			hits,
			hitbox
		);
		shakeCamera_Update
		(
			cameraShake,
			window,
			dt
		);
		doFeed_Update
		(
			{
				window.getSize().x / 2.f,
				25.f
			},
			dt,
			feed
		);
		playSounds_Update(soundEffects);
		delete_Update(dt);

		window.clear();
		// render systems
		zIndex_Render(renderQueue);
		render(window, renderQueue);
		window.display();
	}
}