#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);

	sf::Text text(font);
	entityMakerNC.addComponent
	(
		entity,
		CText
		{
			text,
			str,
			32,
			sf::Color::White,
			TextFormat::MIDDLE
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			4,
			true
		}
	);

	return entity;
}

Entity makeLog
(
	sf::Vector2f pos,
	sf::Font& font,
	sf::Color col,
	std::string str,
	float timer,
	float fadeSet
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);

	sf::Text text(font);
	entityMakerNC.addComponent
	(
		entity,
		CText
		{
			text,
			str,
			32,
			col,
			TextFormat::MIDDLE
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			4,
			true
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CLog
		{
			timer,
			fadeSet,
			fadeSet
		}
	);

	return entity;
}

Entity& makeButton(sf::Vector2f pos, sf::Vector2f size, Scene scene, std::string str, sf::Font& font)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);
	sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
	entityMakerNC.addComponent
	(
		entity,
		CShape
		{
			rect
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			size.x / 2.f,
			size.y / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CButton
		{
			0.125f,
			true
		}
	);

	sf::Text text(font);
	entityMakerNC.addComponent
	(
		entity,
		CText
		{
			text,
			str,
			64,
			sf::Color::Black,
			TextFormat::MIDDLE
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CNextScene
		{
			scene,
			false
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			1,
			true
		}
	);

	return entity;
}

Entity& makeIndicator
(
	sf::Vector2f pos,
	sf::Vector2f size,
	float speed,
	float speedIncrease
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);

	sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
	rect.setFillColor(sf::Color::Blue);

	entityMakerNC.addComponent
	(
		entity,
		CShape{
			rect
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			3,
			true
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			size.x / 2.f,
			size.y / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CVelocity{}
	);
	entityMakerNC.addComponent
	(
		entity,
		CSpeed{ speed }
	);
	entityMakerNC.addComponent
	(
		entity,
		CSpeedIncrease{ speedIncrease }
	);

	return entity;
}

Entity& makeSlider
(
	sf::Vector2f pos,
	sf::Vector2f size,
	sf::Vector2f slider
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);

	sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
	rect.setFillColor(sf::Color::Green);

	entityMakerNC.addComponent
	(
		entity,
		CShape{
			rect
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			1,
			true
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			size.x / 2.f,
			size.y / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CVelocity{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CXBounds
		{
			pos.x - (size.x / 2.f),
			pos.x + (size.x / 2.f)
		}
	);

	return entity;
}

Entity& makeHitbox
(
	Entity slider,
	float startSize,
	float minSize,
	float sizeDecrease
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{
			0.f,
			0.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			0.f,
			0.f
		}
	);

	sf::RectangleShape rect(sf::Vector2f(0.f, 0.f));
	rect.setFillColor(sf::Color::White);

	entityMakerNC.addComponent
	(
		entity,
		CShape{
			rect
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			2,
			true
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			0.f,
			0.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CVelocity{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CXBounds
		{
			0.f,
			0.f
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CHitbox
		{
			slider,
			startSize,
			minSize,
			sizeDecrease
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CScore{}
	);

	return entity;
}

Entity makeCameraShake()
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CCameraShake{}
	);

	return entity;
}

Entity makeFeed()
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CFeed{}
	);

	return entity;
}