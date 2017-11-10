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
	if (!m_font.loadFromFile("../assets/fonts/arial.ttf"))
		std::cout << "CAN'T LOAD FONT" << std::endl;

	m_dayCounterText.setFont(m_font);
	m_dayCounterText.setPosition(400, 20);
	m_dayCounterText.setCharacterSize(30);
	m_dayCounterText.setFillColor(sf::Color::White);

	m_ageText.setFont(m_font);
	m_ageText.setCharacterSize(12);
	m_ageText.setFillColor(sf::Color::White);


	Human* adam = new Human(Human::Gender::MALE);
	adam->SetPosition(random_between(0, 800), random_between(0, 800));
	m_humans.push_back(adam);

	Human* eve = new Human(Human::Gender::FEMALE);
	eve->SetPosition(random_between(0, 800), random_between(0, 800));
	m_humans.push_back(eve);

	m_circleColor.a = 100;
}

void Application::Run()
{
	while(m_window.isOpen() && m_humans.size() > 0)
	{
		Update();
	}

	std::cout << "Colony lifetime : " << m_dayCounter << " days" << std::endl;
	system("PAUSE");
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
		if (*it == nullptr)
			continue;

		Human* h = *it;

		for (auto it2 = m_humans.begin(); it2 != m_humans.end(); ++it2)
		{
			Human* h2 = *it2;
			if (h->CanMeet(h2))
			{
				if (h->GetGender() != h2->GetGender())
				{
					if (h->CanProcreate() && h2->CanProcreate())
					{
						Human* baby = nullptr;
						baby = h->Procreate();
						if (baby)
						{
							h2->Procreate();
						}
						else
						{
							baby = h2->Procreate();
						}

						if (baby)
						{
							baby->SetPosition(h->GetPosition().x, h->GetPosition().y);
							m_humans.push_back(baby);
						}
					}
				}
			}
		}

		h->DayTick();
		if (h->IsDead())
		{
			*it = nullptr;
		}
	}

	++m_dayCounter;
}

void Application::Draw()
{
	for (auto it = m_humans.begin(); it != m_humans.end(); ++it)
	{
		if (*it == nullptr)
			continue;

		Human* h = *it;

		m_socialRadius.setRadius(h->__SOCIAL_RADIUS);
		m_socialRadius.setPosition(h->GetPosition());
		m_socialRadius.move(-h->__SOCIAL_RADIUS, -h->__SOCIAL_RADIUS);
		m_circleColor.r = h->GetColor().r;
		m_circleColor.g = h->GetColor().g;
		m_circleColor.b = h->GetColor().b;
		m_socialRadius.setFillColor(m_circleColor);
		m_window.draw(m_socialRadius);

		m_ageText.setString(std::to_string(h->GetAge()));
		m_ageText.setPosition(h->GetPosition().x, h->GetPosition().y);
		const sf::FloatRect textRect = m_ageText.getLocalBounds();
		m_ageText.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		m_window.draw(m_ageText);
	}

	m_dayCounterText.setString("DAY: " + std::to_string(m_dayCounter));
	const sf::FloatRect textRect = m_dayCounterText.getLocalBounds();
	m_dayCounterText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_window.draw(m_dayCounterText);
}
