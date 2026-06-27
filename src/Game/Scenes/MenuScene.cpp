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
				window.getSize().y / 2.f - 100.f
			}
		),
		sf::Vector2f
		(
			{
				200.f,
				100.f
			}
		),
		TextureEnum::TEXTURE_PLACEHOLDER_PLACEHOLDER,
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
				window.getSize().y / 2.f + 100.f
			}
		),
		sf::Vector2f
		(
			{
				200.f,
				100.f
			}
		),
		TextureEnum::TEXTURE_PLACEHOLDER_PLACEHOLDER,
		"Hard",
		font,
		Scene::PLAYING
	);

	nc.addComponent
	(
		hardMode,
		CMode{ GameMode::MODE_HARD }
	);

	Entity loadedTextures = makeLoadedTexturesContainer();

	// onstart systems
	setText_Start(font); // font system is limited to one font
	setTextOrigin_Start();

	loadTextures_Start(loadedTextures);
	loadSprites_Start(loadedTextures);

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
		nextScene_Update(window, font);

		window.clear();
		// render systems
		zIndex_Render(renderQueue);
		render(window, renderQueue);
		window.display();
	}
}