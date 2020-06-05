#include "stdafx.h"
#include "MapEditorState.h"


void MapEditorState::initKeybinds()
{
	/* Config File*/
	std::fstream fst("Config/config.ini");

	if (fst.is_open())
	{
		for (std::string line; std::getline(fst, line); )
		{

			if (line == "[Keybinds_Name SupportedKeys_Keycap]")
			{
				std::string key_Name = "";
				std::string key_Input = "";

				while (fst >> key_Name >> key_Input)
				{
					if (key_Name == "[Keybinds_Name" && key_Input == "SupportedKeys_End]")
					{
						std::cout << "Brinco MapEditorState <-- \n";
						goto endOfLoop;
					}
					//std::cout << key_Name << " " << key_Input << "\n";

					keybinds[key_Name] = supportedKeys->at(key_Input);
				}
			}
		}
	}
endOfLoop:


	fst.close();

}

void MapEditorState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("images/Player/PlayerS1.png"))
	{
		throw "ERROR : Valio madre no cargo el sprite MapEditorState linea 49";
	}
}

void MapEditorState::initPlayers()
{
	this->player = new Player({ 0, 0 }, &this->textures["PLAYER_IDLE"]);
}

MapEditorState::MapEditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
	initPlayers();
}

void MapEditorState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	player->update(dt);

}

void MapEditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}
	player->render(target);

	ImGui::SFML::Update(*window, deltaClock1.restart());

	ImGui::SetNextWindowSize(ImVec2(0, 0));
	ImGui::Begin("no_name", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
		                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(600, -10));
	ImGui::SetWindowFontScale(1.0f);

	for (int i = 0; i < 4; i++)
	{
		if (i > 0)
		{
			ImGui::PushID(i);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(160, 160, 160));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(192, 192, 192));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(224, 224, 224));
			ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor(0, 0, 0));

			if (i == 1)
			{
				ImGui::Dummy(ImVec2(0.0f, 20.0f));
				ImGui::Button("Map Editor", ImVec2(80, 40));
			}
			if (i == 2)
			{
				ImGui::Dummy(ImVec2(0.0f, 20.0f));
				ImGui::Button("Settings", ImVec2(80, 40));
			}
			if (i == 3)
			{
				ImGui::Dummy(ImVec2(0.0f, 20.0f));
				ImGui::Button("Quit", ImVec2(80, 40));
			}

			ImGui::PopStyleColor(4);
			ImGui::PopID();

			if (i == 1 && ImGui::IsItemClicked(0))
			{
				std::cout << i << "Map Editor \n";
			}
			if (i == 2 && ImGui::IsItemClicked(0))
			{
				std::cout << i << "Settings \n";
			}
			if (i == 3 && ImGui::IsItemClicked(0))
			{
				std::cout << i << "Quit \n";
				endState();
			}
		}
	}

	ImGui::End();
	ImGui::SFML::Render(*window);
}

void MapEditorState::updateInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
	{
		player->move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
	{
		player->move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
	{
		player->move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
	{
		player->move(dt, 0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
	{
		endState();
	}
}

MapEditorState::~MapEditorState()
{
	delete this->player;
}
