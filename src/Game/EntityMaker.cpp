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

Entity& makeButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
	std::string str,
	sf::Font& font,
	Scene scene
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
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);

	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
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
	TextureEnum texture,
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

	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);

	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
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
	TextureEnum texture,
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

	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);

	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
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
	TextureEnum texture,
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

	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);

	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
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

Entity& makeBackground
(
	TextureEnum texture,
	sf::Vector2f size
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{
			size.x / 2.f,
			size.y / 2.f
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

	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);

	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			0,
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

Entity makeLoadedTexturesContainer()
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CTexturesContainer{}
	);

	return entity;
}

Entity makeSoundEffectsContainer()
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CSoundEffectsContainer{}
	);

	return entity;
}

Entity makeSound(SoundEffect type)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CSound{ type }
	);

	return entity;
}

Entity makeSound(SoundEffect type, float pitch)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CSound{ type, pitch }
	);

	return entity;
}