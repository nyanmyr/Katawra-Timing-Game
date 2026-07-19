#include <iostream>
#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void menuScene
(
	sf::RenderWindow& window,
	sf::Font& normalFont,
	sf::Font& titleFont
)
{
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;

	sf::Color themeColor = sf::Color(0, 102, 204);
	sf::Color textColor = sf::Color::White;

	// TODO: make into function
	const float themeBrightness =
		(0.2126 * themeColor.r) +
		(0.7152 * themeColor.g) +
		(0.0722 * themeColor.b);

	//std::cout << "luminance: " << themeBrightness << "\n";

	if (themeBrightness > 186)
	{
		textColor = sf::Color::Black;
	}

	// entity instantiation
	Entity normalMode = makeTextButton
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{
			300.f,
			100.f
		},
		TextureEnum::BUTTON_TEXTURE,
		"Normal",
		normalFont,
		Scene::PLAYING,
		themeColor,
		textColor
	);

	nc.addComponent
	(
		normalMode,
		CMode{ GameMode::MODE_NORMAL }
	);

	Entity hardMode = makeTextButton
	(
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f + 150.f
		},
		{
			300.f,
			100.f
		},
		TextureEnum::BUTTON_TEXTURE,
		"Hard",
		normalFont,
		Scene::PLAYING,
		themeColor,
		textColor
	);

	nc.addComponent
	(
		hardMode,
		CMode{ GameMode::MODE_HARD }
	);

	Entity name = makeUIText
	(
		{
			window.getSize().x / 2.f,
			45.f
		},
		normalFont,
		"Katawra's",
		64,
		textColor
	);

	Entity title = makeUIText
	(
		{
			window.getSize().x / 2.f,
			150.f
		},
		titleFont,
		"Timing Game",
		48,
		textColor
	);

	Entity creator = makeUIText
	(
		{
			window.getSize().x / 2.f,
			550.f
		},
		normalFont,
		"a game by Katawra",
		24,
		textColor
	);


	Entity loadedTextures = makeLoadedTexturesContainer();
	Entity background = makeBackground
	(
		TextureEnum::BACKGROUND_TEXTURE,
		{
			window.getDefaultView().getSize().x + 75.f,
			window.getDefaultView().getSize().y + 75.f
		},
		{
			window.getDefaultView().getSize().x / 2.f,
			window.getDefaultView().getSize().y / 2.f
		},
		themeColor
	);
	Entity soundEffects = makeSoundEffectsContainer();

	const float CORNER_DISTANCE = 50.f;
	const float SMALL_BUTTON_SIZE = 75.f;
	const float FIRST_SMALL_BUTTON_X = CORNER_DISTANCE + (SMALL_BUTTON_SIZE / 2.f);

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
			FIRST_SMALL_BUTTON_X,
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
			FIRST_SMALL_BUTTON_X * 2,
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

	CSoundControl& test = nc.getComponentArray<CSoundControl>()->getData(soundButton);

	Entity sceneTransition = makeSceneTransition
	(
		.5f, // fade in
		.5f // fade out
	);

	Entity musicTrack = makeMusicTrack();

	std::optional<sf::Music> music;

	// onstart systems
	loadMenuTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);
	loadMenuSoundEffects_Start(soundEffects);
	loadMenuMusicTrack(musicTrack);

	while (window.isOpen())
	{
		setText_Start(); // font system is limited to one font

		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

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
		}

		// update systems
		doSoundControl_Update(soundButton);
		doSoundControl_Update(musicButton);
		changeSoundButtonTexture_Update(loadedTextures);

		button_Update
		(
			sf::Vector2i
			(
				worldPos.x,
				worldPos.y
			),
			dt
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
			normalFont,
			titleFont
		);

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