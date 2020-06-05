#pragma once
#include "stdafx.h"

class Entity
{
public:
	Entity();
	void createSprite(sf::Texture* texture);
	virtual void setPosition(const sf::Vector2f position);
	virtual void move(const float& dt, const float dir_x, const float dir_y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	virtual ~Entity();

private:
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	float movementSpeed;
};