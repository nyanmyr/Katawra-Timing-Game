#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

// TODO: adjust volume when fading
// TODO: add background music
// TODO: make mute music and sound effects button (functionality)
// TODO: make adjustable color theme
// TODO: are you sure button prompt main menu button (you should be able to save your progress)
// TODO: save score (make it save when returning to menu)
// TODO: ask to continue if window is abruptly closed
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
	std::string difficultyStr;
	sf::Color difficultyColor;

	switch (difficulty)
	{
		case DIFFICULTY_HARD:
			startingSpeed = 130.f;
			speedIncrease = 30.f;

			startSize = 80.f;
			minSize = 15.f;
			sizeDecrease = 10.f;

			//std::cout << "difficulty: HARD\n";
			difficultyStr = "HARD";
			difficultyColor = sf::Color(204, 102, 0);

			break;
		case DIFFICULTY_NORMAL:
		default:
			startingSpeed = 100.f;
			speedIncrease = 12.5f;

			startSize = 100.f;
			minSize = 20.f;
			sizeDecrease = 5.f;

			//std::cout << "difficulty: NORMAL\n";
			difficultyStr = "NORMAL";
			difficultyColor = sf::Color(0, 102, 204);

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

	Entity difficultyIntro = makeUIText
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		font,
		difficultyStr + " MODE",
		16,
		difficultyColor,
		false
	);

	Entity difficultyText = makeUIText
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y - 25.f
		},
		font,
		difficultyStr + " MODE",
		16,
		difficultyColor,
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
			intro3,
			difficultyIntro
		},
		{
			.5f,
			.5f,
			.75f,
			1.f
		},
		{
			SoundEffect::BLIP1_SOUND_EFFECT,
			SoundEffect::BLIP1_SOUND_EFFECT,
			SoundEffect::BLIP2_SOUND_EFFECT,
			SoundEffect::BLIP1_SOUND_EFFECT
		}
	);

	const float CORNER_DISTANCE = 50.f;
	const float SMALL_BUTTON_SIZE = 75.f;

	Entity menuReturn = makeButton
	(
		{
			CORNER_DISTANCE + (SMALL_BUTTON_SIZE / 2.f),
			window.getSize().y - CORNER_DISTANCE - (SMALL_BUTTON_SIZE / 2.f)
		},
		{
			SMALL_BUTTON_SIZE,
			SMALL_BUTTON_SIZE
		},
		TextureEnum::BUTTON_RETURN_TEXTURE,
		Scene::MENU
	);

	Entity sceneTransition = makeSceneTransition
	(
		.5f, // fade in
		.5f // fade out
	);

	loadPlayingTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);
	loadPlayingSoundEffects_Start(soundEffects);

	Entity hum = makeLoopSound(SoundEffect::HUM_SOUND_EFFECT, 6.25f);

	while (window.isOpen())
	{
		// in this case the extra baggage is afforable :p
		setText_Start(font); // font system is limited to one font

		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

		playIntro_Update
		(
			intro,
			sceneTransition,
			dt
		);

		setTextOrigin_Start();
		setSpriteOrigins_Start();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			if (const auto& mousePress = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePress->button == sf::Mouse::Button::Left)
				{
					buttonClicks_Update
					(
						sceneTransition,
						sf::Vector2i
						(
							worldPos.x,
							worldPos.y
						)
					);
				}
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
						feed,
						sceneTransition
					);
				}
			}
		}

		// update systems
		button_Update
		(
			sf::Vector2i
			(
				worldPos.x,
				worldPos.y
			),
			dt
		);

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
			hitbox,
			hum,
			sceneTransition
		);
		adjustIndicatorSpeed_Update
		(
			inner,
			indicator,
			hitbox,
			sceneTransition
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
		doSceneTransition
		(
			sceneTransition,
			dt,
			window
		);
		nextScene_Update
		(
			sceneTransition,
			window,
			font
		);
		delete_Update(dt);

		window.clear();
		// render systems
		zIndex_Render(renderQueue);
		render(window, renderQueue);
		renderSceneTransition
		(
			window,
			sceneTransition
		);
		window.display();
	}
}