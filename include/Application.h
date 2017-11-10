#pragma once

#include <ctime>
#include <iostream>
#include <list>

#include "Util.h"
#include "Window.h"
#include "Human.h"

class Application
{
public:
	Application();
	~Application();

	void Setup();
	void Run();

	void HandleEvents();

	void Update();

	void Tick();

	void Draw();

private:
	sf::Event m_event;

	std::list<Human*> m_humans;

	sf::Font m_font;
	sf::Text m_dayCounterText;
	sf::Text m_ageText;

	sf::Color m_circleColor;
	sf::CircleShape m_socialRadius;

	uint16_t m_dayCounter;

	Window m_window;
};
