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
	for (int i = 0; i < 100; ++i)
	{
		Human* h = new Human;
		h->SetPosition(random_between(0, 800), random_between(0, 800));
		m_humans.push_back(h);
	}
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
	for (auto it = m_humans.begin(); it != m_humans.end(); ++it)
	{
		Human* h = *it;

		h->DayTick();
	}
}

void Application::Draw()
{
	for (auto it = m_humans.begin(); it != m_humans.end(); ++it)
	{
		Human* h = *it;

		m_socialRadius.setRadius(h->__SOCIAL_RADIUS);
		m_socialRadius.setPosition(h->GetPosition());
		m_socialRadius.move(-h->__SOCIAL_RADIUS, -h->__SOCIAL_RADIUS);
		m_socialRadius.setFillColor(sf::Color(255, 0, 0, 100));
		m_window.draw(m_socialRadius);

		m_thing.setSize(sf::Vector2f(5, 5));
		m_thing.setPosition(h->GetPosition());
		m_thing.move(-m_thing.getSize().x / 2, -m_thing.getSize().y / 2);
		m_thing.setFillColor(h->GetColor());
		m_window.draw(m_thing);
	}
}
