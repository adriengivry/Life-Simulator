#include "Window.h"

Window::Window()
{
	create(sf::VideoMode(800, 800), "Life Simulator");
	setFramerateLimit(60.f);
}

Window::~Window()
{
}
