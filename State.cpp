#include "stdafx.h"
#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window; /* Tiene que ser pointer -> */
	this->supportedKeys = supportedKeys; /* Tiene que ser pointer -> */
	this->states = states; /* Tiene que ser pointer -> */
	quit = false;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::endState()
{
	quit = true;
}

const bool& State::getQuit() const
{
	return quit;
}

State::~State()
{
}
