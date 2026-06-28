#include <iostream>
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

	// entity instantiation
	Entity normalMode = makeButton
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
				300.f,
				100.f
			}
		),
		TextureEnum::BUTTON_TEXTURE,
		"Normal",
		font,
		Scene::PLAYING
	);

	nc.addComponent
	(
		normalMode,
		CMode{ GameMode::MODE_NORMAL }
	);

	Entity hardMode = makeButton
	(
		sf::Vector2f
		(
			{
				window.getSize().x / 2.f,
				window.getSize().y / 2.f + 150.f
			}
		),
		sf::Vector2f
		(
			{
				300.f,
				100.f
			}
		),
		TextureEnum::BUTTON_TEXTURE,
		"Hard",
		font,
		Scene::PLAYING
	);

	Entity name = makeUIText
	(
		{
			window.getSize().x / 2.f,
			45.f
		},
		font,
		"Katawra's",
		64,
		sf::Color::Black
	);

	Entity title = makeUIText
	(
		{
			window.getSize().x / 2.f,
			150.f
		},
		font,
		"Timing Game",
		128,
		sf::Color::Black
	);

	Entity creator = makeUIText
	(
		{
			window.getSize().x / 2.f,
			550.f
		},
		font,
		"a game by Katawra",
		32,
		sf::Color::Black
	);

	nc.addComponent
	(
		hardMode,
		CMode{ GameMode::MODE_HARD }
	);

	Entity loadedTextures = makeLoadedTexturesContainer();
	Entity background = makeBackground
	(
		TextureEnum::BACKGROUND_TEXTURE,
		{
			window.getDefaultView().getSize().x,
			window.getDefaultView().getSize().y
		}
	);
	Entity soundEffects = makeSoundEffectsContainer();

	// onstart systems
	setText_Start(font); // font system is limited to one font
	setTextOrigin_Start();

	loadMenuTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);
	loadMenuSoundEffects_Start(soundEffects);

	setSpriteOrigins_Start();

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
				buttonClicks_Update
				(
					sf::Vector2i
					(
						worldPos.x,
						worldPos.y
					)
				);
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
		playSounds_Update(soundEffects);
		nextScene_Update(window, font);

		window.clear();
		// render systems
		zIndex_Render(renderQueue);
		render(window, renderQueue);
		window.display();
	}
}