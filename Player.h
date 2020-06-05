#pragma once

#include "Entity.h"

class Player :
	public Entity
{
public:
	Player(const sf::Vector2f position, sf::Texture* texture);
	~Player();

private:
	void initVariables();
	void initComponents();

};