#include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
}

void Player::initComponents()
{
}

Player::Player(const sf::Vector2f position, sf::Texture* texture)
{
	initVariables();
	initComponents();
	createSprite(texture);
	setPosition(position);
}


Player::~Player()
{
}
