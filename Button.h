#pragma once
#include "SFML/Graphics.hpp"

enum Button_States
{
	BTN_IDLE,
	BTN_HOVER,
	BTN_ACTIVE
};

class Button
{
public:
	Button(const sf::Vector2f position, const sf::Vector2f size, sf::Font* font, std::string btn_text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	void update(sf::Vector2f mousePos);
	const bool isPressed();
	void render(sf::RenderTarget* target);
	virtual ~Button();

private:

	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

};