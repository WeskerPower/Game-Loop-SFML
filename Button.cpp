#include "stdafx.h"
#include "Button.h"

Button::Button(const sf::Vector2f position, const sf::Vector2f size, sf::Font* font, std::string btn_text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	this->shape.setPosition(position);
	this->shape.setSize(size);
	this->shape.setFillColor(idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(btn_text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	//this->text.setPosition(
	//	this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
	//	this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
	//);

	this->text.setPosition(position);

	const sf::FloatRect bounds(this->text.getLocalBounds());
	const sf::Vector2f box(this->shape.getSize());
	text.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

}


void Button::update(sf::Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

const bool Button::isPressed()
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

Button::~Button()
{
}
