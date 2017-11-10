#include "Application.h"

Application::Application()
{
	Setup();
}

Application::~Application()
{
}

void Application::Setup()
{
	srand(time(nullptr));

	johnny.SetPosition(500, 500);
}

void Application::Run()
{
	while(m_window.isOpen())
	{
		Update();
	}
}

void Application::HandleEvents()
{
	while(m_window.pollEvent(m_event))
	{
		switch (m_event.type)
		{
		default:
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Application::Update()
{
	HandleEvents();

	Tick();

	m_window.clear();

	Draw();

	m_window.display();
}

void Application::Tick()
{
}

void Application::Draw()
{
	// Drawing Johnny
	m_thing.setSize(sf::Vector2f(10, 10));
	m_thing.setPosition(johnny.GetPosition());
	m_thing.move(m_thing.getSize().x / 2, m_thing.getSize().y / 2);
}
