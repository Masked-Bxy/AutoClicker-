// DemoSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "common.h"
#include "Button.hpp"
#include "SFMLtoVK.hpp"
#include "Texture.hpp"

// AutoClick clavier minimal — utilise SendInput pour simuler une touche.
// Compile avec Visual Studio (C++14). Aucun pilote requis.
// Usage : AutoClick.exe [intervalMs] [pressMs] [vkCode]
// Exemple : AutoClick.exe 1000 50 0x20  => appuie sur Espace toutes les 1000ms pendant 50ms

#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>
#include <cstdlib>
#include <iomanip>
#include <fstream>

#define DISABLE_COLOR sf::Color(125, 125, 125);
#define ENABLE_COLOR sf::Color(255, 255, 255);

#define SW (48*4)
#define SH (48*3)

bool Simulate = false;
int milisecond = 10;
bool running = true;
WORD vk;

struct StarterStruct
{
	int ms;
	unsigned int vkCode;
};

const void SendKeyDown(WORD vk)
{
	INPUT input = {};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vk;
	input.ki.dwFlags = 0; // key down
	SendInput(1, &input, sizeof(input));
}

const void SendKeyUp(WORD vk)
{
	INPUT input = {};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vk;
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}

const void SendMouseDownFromVK(WORD vk)
{
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = 0;
    input.mi.mouseData = 0;
    switch (vk)
    {
    case VK_LBUTTON: input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; break;
    case VK_RBUTTON: input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; break;
    case VK_MBUTTON: input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN; break;
    case VK_XBUTTON1: input.mi.dwFlags = MOUSEEVENTF_XDOWN; input.mi.mouseData = XBUTTON1; break;
    case VK_XBUTTON2: input.mi.dwFlags = MOUSEEVENTF_XDOWN; input.mi.mouseData = XBUTTON2; break;
    default: return;
    }
    SendInput(1, &input, sizeof(INPUT));
}

const void SendMouseUpFromVK(WORD vk)
{
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = 0;
    input.mi.mouseData = 0;
    switch (vk)
    {
    case VK_LBUTTON: input.mi.dwFlags = MOUSEEVENTF_LEFTUP; break;
    case VK_RBUTTON: input.mi.dwFlags = MOUSEEVENTF_RIGHTUP; break;
    case VK_MBUTTON: input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP; break;
    case VK_XBUTTON1: input.mi.dwFlags = MOUSEEVENTF_XUP; input.mi.mouseData = XBUTTON1; break;
    case VK_XBUTTON2: input.mi.dwFlags = MOUSEEVENTF_XUP; input.mi.mouseData = XBUTTON2; break;
    default: return;
    }
    SendInput(1, &input, sizeof(INPUT));
}

inline bool IsMouseVK(WORD v)
{
    return v == VK_LBUTTON || v == VK_RBUTTON || v == VK_MBUTTON || v == VK_XBUTTON1 || v == VK_XBUTTON2;
}

// Remplace la fonction SimulatedClick existante par celle-ci
void SimulatedClick()
{
    while (running)
    {
        while (Simulate)
        {
            WORD curVk = vk; // copie pour réduire la fenêtre de race entre threads
            if (IsMouseVK(curVk))
            {
                SendMouseDownFromVK(curVk);
                std::this_thread::sleep_for(std::chrono::milliseconds(milisecond / 2));
                SendMouseUpFromVK(curVk);
                std::this_thread::sleep_for(std::chrono::milliseconds(milisecond / 2));
            }
            else
            {
                SendKeyDown(curVk);
                std::this_thread::sleep_for(std::chrono::milliseconds(milisecond / 2));
                SendKeyUp(curVk);
                std::this_thread::sleep_for(std::chrono::milliseconds(milisecond / 2));
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Retourne le chemin complet du fichier de sauvegarde dans %APPDATA%\ .AutoClicked\config.save
const std::string GetSaveFilePath()
{
	char buffer[MAX_PATH] = { 0 };
	DWORD len = GetEnvironmentVariableA("APPDATA", buffer, MAX_PATH);
	std::string basePath;
	if (len > 0 && len < MAX_PATH)
	{
		basePath = std::string(buffer); // ex: C:\Users\<User>\AppData\Roaming
	}
	else
	{
		// fallback sur le dossier courant si APPDATA introuvable
		basePath = ".";
	}

	std::string dir = basePath + "\\.AutoClicked";

	// Crée le répertoire s'il n'existe pas.
	// CreateDirectoryA retourne FALSE si le dossier existe déjà — on n'a pas besoin de traiter l'erreur ici.
	CreateDirectoryA(dir.c_str(), NULL);

	std::string fullPath = dir + "\\config.save";
	return fullPath;
}

const void UpdateText(sf::Text& _text, char* _str, sf::Vector2f _ratio)
{
	_text.setString(_str);
	sf::Vector2f size = _text.getGlobalBounds().size;
	sf::Vector2f dimR = { (float)size.x * _ratio.x , (float)size.y * _ratio.y };
	_text.setOrigin(dimR);
}

const void UpdateText(sf::Text& _text, char* _str, sf::Vector2f _ratio, int _characterSize)
{
	_text.setCharacterSize(_characterSize);
	_text.setString(_str);
	sf::Vector2f size = _text.getGlobalBounds().size;
	sf::Vector2f dimR = { (float)size.x * _ratio.x , (float)size.y * _ratio.y };
	_text.setOrigin(dimR);
}

const void SaveConfig(StarterStruct _save)
{
	std::fstream file(GetSaveFilePath().c_str(), std::ios::binary | std::ios::out);
	if (!file.is_open())
	{
		return;
	}
	{
		file.write((const char*)&_save.ms, sizeof(int));
		file.write((const char*)&_save.vkCode, sizeof(unsigned int));
		file.close();
	}

}

const StarterStruct LoadConfig()
{
	StarterStruct temp = { 50 ,VK_GAMEPAD_LEFT_SHOULDER };
	std::ifstream file(GetSaveFilePath().c_str(), std::ios::binary | std::ios::in);
	if (!file.is_open())
	{
		std::cout << "No config file found, using defaults." << std::endl;
		return temp;
	}
	{
		file.read((char*)&temp.ms, sizeof(int));
		file.read((char*)&temp.vkCode, sizeof(unsigned int));

		file.close();
	}

	return temp;
}

int main()
{
	sf::RenderWindow window;
	sf::Image icon;
	icon.loadFromMemory(LOGO, LOGOlength);
	window.create(sf::VideoMode(sf::Vector2u(SW, SH)), "AutoClicked!", sf::Style::None);
	window.setIcon(sf::Vector2u(48, 48), icon.getPixelsPtr());
	window.setKeyRepeatEnabled(false);


	sf::RenderTexture renderTexture({ SW, SH });

	sf::Sprite renderSprite(renderTexture.getTexture());

	sf::Shader shader;
	shader.loadFromMemory(GetShader(), sf::Shader::Type::Fragment);
	shader.setUniform("color", sf::Glsl::Vec3(1.0f, 0.0f, 1.0f));
	sf::Texture baseTex;
	baseTex.loadFromMemory(BUTTONSPRITE, BUTTONSPRITElength);
	sf::Sprite baseSp(baseTex);
	baseSp.setScale({ 4,4 });

	sf::Clock clock;
	Button::SetSprite(&baseSp);

	std::vector<Button> buttons;
	for (int i = 0; i < 7; i++)
	{
		buttons.push_back(Button(sf::IntRect(sf::Vector2i(0, (48 / 4) * i), sf::Vector2i(48 / 4, 48 / 4)), sf::Vector2f(float((48 / 4) * i), 0.f)));
	}

	StarterStruct sav = LoadConfig();

	buttons[0].m_position = { 48,48 };
	buttons[1].m_position = { 48,48 };
	buttons[2].m_position = { 96,48 };
	buttons[3].m_position = { 0,48 };
	buttons[4].m_position = { 144,48 };
	buttons[5].m_position = { 144,0 };
	buttons[6].m_position = { 144,96 };

	int id = -1;
	vk = (WORD)sav.vkCode;
	milisecond = Clamp(sav.ms, 10, 1000);

	sf::Font font;
	font.openFromMemory(PIX32,PIX32length);
	sf::Text text(font);
	text.setCharacterSize(48);
	UpdateText(text, (char*)(std::to_string(milisecond) + ":ms").c_str(), { 1.f, 0.f });
	text.setPosition({ 48 * 3.0f - 4, -12.0f });

	sf::Text motd(font);
	motd.setCharacterSize(50);
	UpdateText(motd, (char*)"STOPPING!", { 0.5f, 0.5f });
	motd.setPosition({ 48 * 2.0f, 48.f - 12.0f });
	motd.setFillColor(sf::Color(255, 0, 0));

	sf::Text VkV(font);
	VkV.setCharacterSize(24);

	VkV.setPosition({ 48 * 3.0f / 2.f, 96.f });
	UpdateText(VkV, (char*)VirtualKeyToString(vk).c_str(), { 0.5f, 0.f });
	VkV.setFillColor(sf::Color::White);

	sf::Vector2i offset = { 0,0 };

	bool tracking = false;

	bool mapping = false;

	std::thread clickThread(SimulatedClick);

	shader.setUniform("color", sf::Glsl::Vec3(0.95f, 1.0f, 0.95f));

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (const auto* MousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (MousePressed->button == sf::Mouse::Button::Left)
				{
					id = -1;
					for (int i = 0; i < buttons.size(); i++)
					{
						if (buttons[i].Click(window))
						{
							if ((Simulate ? 1 : 0) != i)
							{
								id = i;
								i = (int)buttons.size();
							}
						}
						switch (id)
						{
						case 5:
							offset = sf::Mouse::getPosition() - window.getPosition();
							tracking = true;
							break;
						}
					}

				}
			}
			else if (const auto* MouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (id >= 0 && MouseReleased->button == sf::Mouse::Button::Left)
				{
					buttons[id].Release();
					switch (id)
					{
					case 0:
						Simulate = false;
						buttons[2].m_color = ENABLE_COLOR;
						buttons[3].m_color = ENABLE_COLOR;
						shader.setUniform("color", sf::Glsl::Vec3(0.95f, 1.0f, 0.95f));
						break;
					case 1:
						if (!mapping)
						{
							Simulate = true;
							buttons[2].m_color = DISABLE_COLOR;
							buttons[3].m_color = DISABLE_COLOR;
							shader.setUniform("color", sf::Glsl::Vec3(0.05f, 0.5f, 0.25f));
						}
						break;
					case 2:
						if (!Simulate)
						{
							milisecond = Clamp(milisecond + 10, 10, 1000);

							UpdateText(text, (char*)(std::to_string(milisecond) + ":ms").c_str(), { 1.f, 0.f });
						}
						break;
					case 3:
						if (!Simulate)
						{
							milisecond = Clamp(milisecond - 10, 10, 1000);

							UpdateText(text, (char*)(std::to_string(milisecond) + ":ms").c_str(), { 1.f, 0.f });
						}
						break;
					case 4:
						Simulate = false;
						running = false;
						shader.setUniform("color", sf::Glsl::Vec3(0.25f, 0.0f, 0.0f));
						buttons[2].m_color = ENABLE_COLOR;
						buttons[3].m_color = ENABLE_COLOR;
						break;
					case 5:
						tracking = false;
						break;
					case 6:
						if (!Simulate)
						{
							mapping = true;
							UpdateText(VkV, (char*)"select key", { 0.5f, 0.f }, 24);
						}
					default:

						break;
					}
				}
			}
			if (mapping)
			{
				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
				{

					vk = SfmlKeyToVirtualKey(keyPressed->code);
					mapping = false;
					UpdateText(VkV, (char*)VirtualKeyToString(vk).c_str(), { 0.5f, 0.f }, 24);
				}
				else if (const auto* joyPressed = event->getIf<sf::Event::JoystickButtonPressed>())
				{
					vk = SfmlJoystickButtonToVirtualKey(joyPressed->button);
					mapping = false;
					UpdateText(VkV, (char*)VirtualKeyToString(vk).c_str(), { 0.5f, 0.f }, 24);
				}
				else if (const auto* MousePressed = event->getIf<sf::Event::MouseButtonPressed>())
				{
					vk = SfmlMouseButtonToVirtualKey(int(MousePressed->button));
					mapping = false;
					UpdateText(VkV, (char*)VirtualKeyToString(vk).c_str(), { 0.5f, 0.f }, 24);
				}
			}
		}
		float dt = clock.restart().asSeconds();

		if (tracking)
		{
			sf::Vector2i mPos = sf::Mouse::getPosition();
			sf::Vector2i moffset = mPos - offset;
			window.setPosition(moffset);
		}

		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].Update(window, dt);
		}


		//RENDER
		renderTexture.clear(sf::Color::Black);
		sf::IntRect temp(sf::Vector2i(0, 48/4 * 7), sf::Vector2i(48/4 * 3, 48/4));
		baseSp.setTextureRect(temp);
		renderTexture.draw(VkV);
		baseSp.setPosition({ 0,48 * 2 });
		renderTexture.draw(baseSp);

		for (int i = 0; i < buttons.size(); i++)
		{
			if ((Simulate ? 1 : 0) != i)
			{
				buttons[i].Draw(renderTexture);
			}
		}

		renderTexture.draw(text);

		baseSp.setPosition({ 0,0 });

		baseSp.setColor(text.getFillColor());


		baseSp.setTextureRect(temp);
		renderTexture.draw(baseSp);

		renderTexture.display();

		window.clear(sf::Color::Black);

		window.draw(renderSprite, &shader);
		if (!running)
		{
			window.draw(motd);
		}
		window.display();

		if (!running)
		{
			clickThread.join();
			window.close();
		}
	}
	SaveConfig({ milisecond, vk });
}
