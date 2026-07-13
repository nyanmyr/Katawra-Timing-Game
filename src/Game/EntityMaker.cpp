#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

// TODO: is it better to merge these into one?
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

	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			0.f,
			0.f
		}
	);

	return entity;
}

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str,
	int size,
	sf::Color col
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
			size,
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
		CTransform
		{
			0.f,
			0.f
		}
	);

	return entity;
}

Entity makeUIText
(
	sf::Vector2f pos,
	sf::Font& font,
	std::string str,
	int size,
	sf::Color col,
	bool visible
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
			size,
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
			visible
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

	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			0.f,
			0.f
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
	entityMakerNC.addComponent
	(
		entity,
		CButtonSounds{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
	);

	return entity;
}
Entity& makeButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture,
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
	entityMakerNC.addComponent
	(
		entity,
		CButtonSounds{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
	);

	return entity;
}
Entity& makeButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture
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
		CButtonSounds{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
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
			4,
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

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
	);

	return entity;
}

Entity& makeInnerBar
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
		CXBounds
		{
			pos.x - (size.x / 2.f),
			pos.x + (size.x / 2.f)
		}
	);

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
	);

	return entity;
}

Entity& makeObject
(
	TextureEnum texture,
	sf::Vector2f pos,
	sf::Vector2f size,
	int index
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
			index,
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
		CDoSpriteCenter{}
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

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
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

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
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

Entity makeLoopSound(SoundEffect type, float volume)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CSound{ type, true, volume }
	);

	return entity;
}

Entity& makeSoundButton
(
	sf::Vector2f pos,
	sf::Vector2f size,
	TextureEnum texture
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
		CButtonSounds{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CDoSpriteCenter{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CSoundControl{}
	);

	return entity;
}

Entity makeMusic(Music type)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CMusic{ type }
	);

	return entity;
}

Entity makeMusicTrack()
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CMusicTrack{}
	);

	return entity;
}

Entity makeIntro
(
	const std::vector<Entity>& texts,
	const std::vector<float>& timers,
	const std::vector<SoundEffect>& soundEffects
)
{
	Entity entity = entityMakerNC.createEntity();

	std::queue<Entity> tempTexts;
	std::queue<std::pair<float, float>> tempTimers;
	std::queue<SoundEffect> tempSoundEffects;

	for (Entity entity : texts)
	{
		tempTexts.push(entity);
	}

	for (float timer : timers)
	{
		tempTimers.push({ timer , timer });
	}

	for (SoundEffect soundEffect : soundEffects)
	{
		tempSoundEffects.push(soundEffect);
	}

	entityMakerNC.addComponent
	(
		entity,
		CIntro
		{
			tempTexts,
			tempTimers,
			tempSoundEffects
		}
	);

	return entity;
}

Entity makeSceneTransition
(
	float fadeinTimer,
	float fadeoutTimer
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CSceneTransition
		{
			fadeinTimer,
			fadeoutTimer
		}
	);

	return entity;
}
