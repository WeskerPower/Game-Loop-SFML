#pragma once
#include "Player.h"
#include "imgui.h"
#include "imgui-SFML.h"

class State
{
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	/* para convertir en virtuals puros se iguala a cero y si no inicias los valores esta madre se va caer mas rapido que la tanga de la panini */
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePositions();
	void endState();
	const bool& getQuit() const;
	virtual ~State();

private:



protected:

	virtual void initKeybinds() = 0;

	sf::RenderWindow* window;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::map<std::string, sf::Texture> textures;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::stack<State*>* states;

	bool quit;

};