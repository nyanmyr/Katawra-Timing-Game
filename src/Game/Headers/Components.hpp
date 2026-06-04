#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"
#include <optional>
#include <string>

enum TextFormat
{
	TOP,
	MIDDLE,
	BOTTOM
};

struct CPosition
{
	float x, y;
};

struct CShape
{
	sf::RectangleShape rect;
};

struct CTransform
{
	float width = 0.f, height = 0.f;
	CTransform() = default;
	CTransform(const float width, const float height) :
		width(width), height(height) {
	};
};

struct COrigin
{
	float offsetX = 0.f, offsetY = 0.f;
	COrigin() = default;
	COrigin(const float offsetX, const float offsetY) :
		offsetX(offsetX), offsetY(offsetY) {};
};

struct CButton
{
	float clickedDuration, clickedTimer = 0.f;
	bool clicked = false, enabled = true;

	CButton() = default;
	CButton(const float clickedDuration, const bool enabled) :
		clickedDuration(clickedDuration), enabled(enabled) {};
};

struct CText
{
	std::optional<sf::Text> box;
	std::string string = " ";
	int size = 12;
	sf::Color color;
	TextFormat format;

	CText() = default;
	CText(sf::Text box, std::string string, int size, sf::Color color, TextFormat format) :
		box(box), string(string), size(size), color(color), format(format) {};
};

struct CNextScene
{
	Scene next;
	bool active;
};

struct CZIndex
{
	int index = true;
	bool visible = true;

	CZIndex() = default;
	CZIndex(int index, bool visible) :
		index(index), visible(visible) {
	};
};

struct CVelocity
{
	float x = 0.f, y = 0.f, minX = 0.f, minY = 0.f, maxX = 0.f, maxY = 0.f;

	CVelocity() = default;
	CVelocity(float minX, float minY, float maxX, float maxY) :
		minX(minX), minY(minY), maxX(maxX), maxY(maxY) {};
};

struct CSpeed
{
	float x = 0.f, y = 0.f;

	CSpeed() = default;
	CSpeed(float x, float y) :
		x(x), y(y) {};
};

struct CPlayerController
{
	bool enabled = false;
};

struct CDrag
{
	float x = 0.f, y = 0.f;

	CDrag() = default;
	CDrag(float x, float y) :
		x(x), y(y) {
	};
};

#endif