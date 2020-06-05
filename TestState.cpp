#include "stdafx.h"
#include "TestState.h"


void TestState::initVariables()
{
}

void TestState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!backgroundTexture.loadFromFile("images/Background.png"))
	{
		throw "ERROR : TestState El fondo valio madre";
	}

	background.setTexture(&this->backgroundTexture);
}

void TestState::initKeybinds()
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
						std::cout << "Brinco TestState <-- \n";
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

void TestState::initFonts()
{
	if (!font.loadFromFile("Fonts/Early GameBoy.ttf"))
	{
		throw("ERROR :: Font wont load, main menu line 48");
	}
}

TestState::TestState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initKeybinds();
	initFonts();
}

void TestState::update(const float& dt)
{
	updateInput(dt);
	updateMousePositions();
}



void TestState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	target->draw(background);

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
			//ImGui::SameLine();
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
				this->states->push(new MapEditorState(this->window, this->supportedKeys, this->states));
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

	/*window pos reader*/
	//sf::Text mouseText;
	//mouseText.setPosition(mousePosView);
	//mouseText.setOrigin(10.f,-20.f);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << mousePosView.x << "  " << mousePosView.y;
	//mouseText.setString(ss.str());
	//target->draw(mouseText);
}

void TestState::updateInput(const float& dt)
{

}

TestState::~TestState()
{
}
