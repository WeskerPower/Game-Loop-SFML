#include "stdafx.h"
#include "MapEditor.h"

void MapEditor::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void MapEditor::initWindow()
{
	/* Config File*/
	std::fstream fst("Config/config.ini");
	videoModes = sf::VideoMode::getFullscreenModes();
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (fst.is_open())
	{
		for (std::string line; std::getline(fst, line); )
		{
			{
				if (line == "[Title]")
				{
					fst >> title;
				}
				else if (line == "[Window Dimensions]")
				{
					fst >> window_bounds.width >> window_bounds.height;
				}
				else if (line == "[Full Screen]")
				{
					fst >> fullscreen;
				}
				else if (line == "[Frame Limit]")
				{
					fst >> framerate_limit;
				}
				else if (line == "[Vertical Sync]")
				{
					fst >> vertical_sync_enabled;
				}
				else if (line == "[Antialiasing Level]")
				{
					fst >> antialiasing_level;
				}
				else if (line == "[Supported_Keys Key_Number]")
				{
					std::cout << "Brinco initWindow <-- \n";
					goto endOfLoop;
				}
			}
		}
	}
endOfLoop:

	std::cout << title << std::endl;
	std::cout << window_bounds.width << " / " << window_bounds.height << std::endl;
	std::cout << fullscreen << std::endl;
	std::cout << framerate_limit << std::endl;
	std::cout << vertical_sync_enabled << std::endl;
	std::cout << antialiasing_level << std::endl;
	fst.close();


	windowSettings.antialiasingLevel = antialiasing_level;
	if (fullscreen)
	{
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	}

	window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);
	ImGui::SFML::Init(*window);
}

void MapEditor::initKeys()
{
	/* Config File*/
	std::fstream fst("Config/config.ini");

	if (fst.is_open())
	{
		for (std::string line; std::getline(fst, line); )
		{

			if (line == "[Supported_Keys Key_Number]")
			{
				std::string key = "";
				int key_value = 0;

				while (fst >> key >> key_value)
				{
					if (key == "[Supported_Keys_End]")
					{
						std::cout << "Brinco initKeys <-- \n";
						goto endOfLoop;
					}

					supportedKeys[key] = key_value;
				}
			}
		}
	}
endOfLoop:

	fst.close();

	/* Debug */
	for (auto i : supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void MapEditor::initStates()
{
	states.push(new TestState(this->window, &this->supportedKeys, &this->states));
}


MapEditor::MapEditor()
{
	initWindow();
	initKeys();
	initStates();
}

void MapEditor::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		ImGui::SFML::ProcessEvent(sfEvent);
		if (sfEvent.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}

void MapEditor::updateDt()
{
	/* Actualiza tiempo de render por frame */
	dt = dtClock.restart().asSeconds();
	/* Console Check */
	//system("CLS");
	//std::cout << dt;
}

void MapEditor::update()
{
	updateSFMLEvents();

	/* Actualizar States */
	if (!states.empty())
	{
		states.top()->update(dt);

		if (states.top()->getQuit())
		{
			states.top()->endState();
			delete states.top();
			states.pop();
		}
	}
	else
	{
		endApplication();
		window->close();
	}
	/* close app*/
}

void MapEditor::render()
{
	window->clear(sf::Color(100, 0, 0, 255));

	/* Iniciar States */
	if (!states.empty())
	{
		states.top()->render();
	}

	window->display();
}

void MapEditor::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

void MapEditor::endApplication()
{
	std::cout << "Ending Application \n";
}

MapEditor::~MapEditor()
{
	delete window;
	ImGui::SFML::Shutdown();

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}
