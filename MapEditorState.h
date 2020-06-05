#pragma once
#include "State.h"

class MapEditorState :
	public State
{
public:
	MapEditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	void update(const float& dt); /* State Virtual */
	void render(sf::RenderTarget* target = NULL);  /* State Virtual */
	virtual void updateInput(const float& dt);
	virtual ~MapEditorState();

private:
	void initKeybinds();
	void initTextures();
	void initPlayers();

	Player* player;

	sf::Clock deltaClock1;
	sf::Event sfEvent1;
};