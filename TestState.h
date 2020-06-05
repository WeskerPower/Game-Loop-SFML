#pragma once
#include "MapEditorState.h"

class TestState :
	public State
{
public:
	TestState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	void update(const float& dt); /* State Virtual */
	void render(sf::RenderTarget* target = NULL);  /* State Virtual */
	virtual void updateInput(const float& dt);
	virtual ~TestState();

private:
	void initVariables();
	void initBackground();
	void initKeybinds();
	void initFonts();

	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;
	sf::Clock deltaClock1;
	sf::Event sfEvent1;
};