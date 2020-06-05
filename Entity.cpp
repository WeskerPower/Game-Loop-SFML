#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	texture = NULL;
	sprite = NULL;
	movementSpeed = 100.f;
}

Entity::Entity()
{
	initVariables();
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}

void Entity::setPosition(const sf::Vector2f position)
{
	if (this->sprite)
	{
		this->sprite->setPosition(position);
	}
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->sprite)
	{
		this->sprite->move(dir_x * movementSpeed * dt, dir_y * movementSpeed * dt);
	}
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
}

Entity::~Entity()
{
	delete this->sprite;
}
