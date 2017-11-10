#pragma once

#include <ctime>
#include <iostream>

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

	Human johnny;

	sf::RectangleShape m_thing;
	sf::CircleShape m_socialRange;

	Window m_window;
};
