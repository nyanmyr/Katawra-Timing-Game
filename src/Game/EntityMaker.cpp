#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

Entity& makePlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f minVelocity, sf::Vector2f maxVelocity, sf::Vector2f speed, sf::Vector2f drag)
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
		CVelocity
		{
			minVelocity.x,
			minVelocity.y,
			maxVelocity.x,
			maxVelocity.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CSpeed
		{
			speed.x,
			speed.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CDrag
		{
			drag.x,
			drag.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CPlayerController
		{
			true
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