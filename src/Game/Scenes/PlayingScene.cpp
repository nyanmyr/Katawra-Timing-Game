#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

// TODO: make theme editor button
// TOOD: create themeBrightness adjustment function
// TODO: make adjustable color theme (must be saved)
// TODO: are you sure button prompt main menu button (you should be able to save your progress)
// TODO: save score (make it save when returning to menu)
// TODO: ask to continue if window is abruptly closed
// TODO: make the window resizeable?
// TODO: bug fixing
// FIX: look into checking the sound array to see if its all actually deleted
// FIX: when adjusting volume, sprite color is not adjusted
// TODO: publish

void PlayingScene(sf::RenderWindow& window, sf::Font& font, Difficulty difficulty) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;

	float startingSpeed;
	float speedIncrease;
	float startSize;
	float minSize;
	float sizeDecrease;
	std::string difficultyStr;
	sf::Color difficultyColor;

	sf::Color themeColor = sf::Color(0, 102, 204);
	sf::Color textColor = sf::Color::White;

	const float themeBrightness =
		(0.2126 * themeColor.r) +
		(0.7152 * themeColor.g) +
		(0.0722 * themeColor.b);

	//std::cout << "luminance: " << themeBrightness << "\n";

	if (themeBrightness > 186)
	{
		textColor = sf::Color::Black;
	}

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
			difficultyColor = sf::Color // gets the complementary color
			(
				255 - themeColor.r,
				255 - themeColor.g,
				255 - themeColor.b
			);

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
			difficultyColor = themeColor;

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
		sizeDecrease, // size decrease
		themeColor
	);

	Entity score = makeUIText
	(
		{
			100.f,
			25.f
		},
		font,
		"Score: ",
		32,
		textColor
	);

	Entity hits = makeUIText
	(
		{
			100.f,
			75.f
		},
		font,
		"Hits: ",
		32,
		textColor
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
		textColor,
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
		textColor,
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
		textColor,
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
		},
		themeColor
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
	const float FIRST_SMALL_BUTTON_X = CORNER_DISTANCE + (SMALL_BUTTON_SIZE / 2.f);

	Entity menuReturn = makeButton
	(
		{
			FIRST_SMALL_BUTTON_X,
			window.getSize().y - CORNER_DISTANCE - (SMALL_BUTTON_SIZE / 2.f)
		},
		{
			SMALL_BUTTON_SIZE,
			SMALL_BUTTON_SIZE
		},
		TextureEnum::BUTTON_RETURN_TEXTURE,
		Scene::MENU,
		themeColor
	);

	DSoundStatus soundStatusData;
	loadSoundStatusData_Start(soundStatusData);

	TextureEnum soundTextureEnum = TextureEnum::BUTTON_SOUND_3_TEXTURE;
	TextureEnum musicTextureEnum = TextureEnum::BUTTON_MUSIC_3_TEXTURE;

	adjustSoundTextureEnum_Start
	(
		soundStatusData,
		soundTextureEnum
	);
	adjustMusicTextureEnum_Start
	(
		soundStatusData,
		musicTextureEnum
	);

	Entity musicButton = makeSoundButton
	(
		{
			FIRST_SMALL_BUTTON_X * 2,
			window.getSize().y - CORNER_DISTANCE - (SMALL_BUTTON_SIZE / 2.f)
		},
		{
			SMALL_BUTTON_SIZE,
			SMALL_BUTTON_SIZE
		},
		musicTextureEnum,
		{
			{ESoundStatus::QUARTER_SOUND, TextureEnum::BUTTON_MUSIC_1_TEXTURE},
			{ESoundStatus::HALF_SOUND, TextureEnum::BUTTON_MUSIC_2_TEXTURE},
			{ESoundStatus::FULL_SOUND, TextureEnum::BUTTON_MUSIC_3_TEXTURE},
			{ESoundStatus::MUTED_SOUND, TextureEnum::BUTTON_MUSIC_OFF_TEXTURE}
		},
		soundStatusData.musicStatus,
		themeColor
	);

	Entity soundButton = makeSoundButton
	(
		{
			FIRST_SMALL_BUTTON_X * 3,
			window.getSize().y - CORNER_DISTANCE - (SMALL_BUTTON_SIZE / 2.f)
		},
		{
			SMALL_BUTTON_SIZE,
			SMALL_BUTTON_SIZE
		},
		soundTextureEnum,
		{
			{ESoundStatus::QUARTER_SOUND, TextureEnum::BUTTON_SOUND_1_TEXTURE},
			{ESoundStatus::HALF_SOUND, TextureEnum::BUTTON_SOUND_2_TEXTURE},
			{ESoundStatus::FULL_SOUND, TextureEnum::BUTTON_SOUND_3_TEXTURE},
			{ESoundStatus::MUTED_SOUND, TextureEnum::BUTTON_SOUND_OFF_TEXTURE}
		},
		soundStatusData.soundStatus,
		themeColor
	);

	Entity sceneTransition = makeSceneTransition
	(
		.5f, // fade in
		.5f // fade out
	);

	Entity musicTrack = makeMusicTrack();

	loadPlayingTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);
	loadPlayingSoundEffects_Start(soundEffects);
	loadPlayingMusicTrack(musicTrack);
	std::optional<sf::Music> music;

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
		setColor_Update();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				saveSoundStatusData_Update
				(
					soundStatusData,
					soundButton,
					musicButton
				);
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
						themeBrightness,
						themeColor,
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
		doSoundControl_Update(soundButton);
		doSoundControl_Update(musicButton);
		changeSoundButtonTexture_Update(loadedTextures);
		// NOTE: minor bug; one frame of the changed texture is not centered

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
		playSounds_Update
		(
			soundEffects,
			sceneTransition,
			soundButton
		);
		playMusic_Update
		(
			musicTrack,
			sceneTransition,
			musicButton,
			music
		);
		doSceneTransition
		(
			sceneTransition,
			dt,
			window
		);
		nextSceneSaveSoundStatusData_Update
		(
			soundStatusData,
			soundButton,
			musicButton
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