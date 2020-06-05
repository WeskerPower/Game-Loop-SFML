#pragma once
#include "stdafx.h"
#include "TestState.h"
#include "MapEditorState.h"


class MapEditor
{
public:
	MapEditor();
	void updateSFMLEvents();
	void updateDt();
	void update();
	void render();
	void run();
	void endApplication();
	virtual ~MapEditor();

private:
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	sf::ContextSettings windowSettings;

	std::vector<sf::VideoMode> videoModes;
	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float dt;
	bool fullscreen;
};
