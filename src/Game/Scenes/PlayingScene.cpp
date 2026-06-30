#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

// TODO: return to main menu button
// TODO: make mute music and sound effects button
// TODO: add background music
// TODO: move toward center sound effect
// TODO: bug fixing
// FIX: no delay upon clicking button (directly enters next scene)
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
		TextureEnum::INDICATOR_TEXTURE,
		{
			window.getSize().x / 2.f,
			(window.getSize().y / 2.f) - 11.f
		},
		{
			25.f,
			25.f
		},
		startingSpeed,
		speedIncrease
	);

	Entity inner = makeInnerBar
	(
		TextureEnum::INNER_TEXTURE,
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{ // xbounds is tied to size
			501.f,
			14.f
		},
		{ // inner min/ max
			0.f,
			100.f
		}
	);

	Entity outer = makeObject
	(
		TextureEnum::OUTER_TEXTURE,
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{ // xbounds is tied to size
			509.f,
			23.f
		},
		3
	);

	Entity hitbox = makeHitbox
	(
		TextureEnum::FILL_TEXTURE,
		inner,
		startSize, // start size
		minSize, // min size
		sizeDecrease // size decrease
	);

	Entity score = makeUIText
	(
		{
			100.f,
			25.f
		},
		font,
		"Score: "
	);

	Entity hits = makeUIText
	(
		{
			100.f,
			75.f
		},
		font,
		"Hits: "
	);

	Entity intro1 = makeUIText
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		font,
		"TIME",
		16,
		sf::Color::Black,
		false
	);

	Entity intro2 = makeUIText
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		font,
		"IT",
		16,
		sf::Color::Black,
		false
	);

	Entity intro3 = makeUIText
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		font,
		"RIGHT!",
		16,
		sf::Color::Black,
		false
	);

	Entity cameraShake = makeCameraShake();
	Entity feed = makeFeed();
	Entity loadedTextures = makeLoadedTexturesContainer();
	Entity soundEffects = makeSoundEffectsContainer();
	Entity background = makeBackground
	(
		TextureEnum::BACKGROUND_TEXTURE,
		{
			window.getDefaultView().getSize().x,
			window.getDefaultView().getSize().y
		}
	);
	Entity intro = makeIntro
	(
		{
			intro1,
			intro2,
			intro3
		},
		{
			.5f,
			.5f,
			.75f
		},
		{
			SoundEffect::BLIP1_SOUND_EFFECT,
			SoundEffect::BLIP1_SOUND_EFFECT,
			SoundEffect::BLIP2_SOUND_EFFECT
		}
	);

	loadPlayingTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);
	loadPlaySoundEffects_Start(soundEffects);

	while (window.isOpen())
	{
		// in this case the extra baggage is afforable :p
		setText_Start(font); // font system is limited to one font
		setSpriteOrigins_Start();

		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

		playIntro_Update
		(
			intro,
			dt
		);

		setTextOrigin_Start();

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
			inner,
			dt
		);
		moveIndicator_Update
		(
			indicator,
			inner,
			hitbox
		);
		adjustIndicatorSpeed_Update
		(
			inner,
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