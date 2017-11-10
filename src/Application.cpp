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
	m_ageText.setCharacterSize(20);
	m_ageText.setFillColor(sf::Color::White);

	m_nameText.setFont(m_font);
	m_nameText.setCharacterSize(15);
	m_nameText.setFillColor(sf::Color::White);


	Human* adam = new Human(Human::Gender::MALE);
	adam->SetPosition(random_between(0, 800), random_between(0, 800));
	adam->SetName("adam");
	m_humans.push_back(adam);

	Human* eve = new Human(Human::Gender::FEMALE);
	eve->SetPosition(random_between(0, 800), random_between(0, 800));
	eve->SetName("eve");
	m_humans.push_back(eve);

	m_circleColor.a = 100;
}

void Application::Run()
{
	while(m_window.isOpen() && m_humans.size() > 0)
	{
		Update();
	}

	std::cout << "Colony lifetime : " << m_dayCounter << " days (" << m_dayCounter / 365 << " years)" << std::endl;
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
							std::cout << "[" << m_dayCounter << "] " << h->GetName() << " and " << h2->GetName() << " created " << baby->GetName() << std::endl;
							baby->SetPosition(h->GetPosition().x, h->GetPosition().y);
							m_humans.push_back(baby);
						}
						else
						{
							std::cout << "[" << m_dayCounter << "] " << h->GetName() << " and " << h2->GetName() << " failed creating a baby" << std::endl;
						}
					}
				}
			}
		}

		h->DayTick();
		if (h->IsDead())
		{
			std::cout << "[" << m_dayCounter << "] " << h->GetName() << " died after " << std::to_string(h->GetAge()) << " years" << std::endl;
			delete *it;
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

		m_nameText.setString(h->GetName());
		m_nameText.setPosition(h->GetPosition().x, h->GetPosition().y - h->__SOCIAL_RADIUS - 10);
		const sf::FloatRect textRect2 = m_nameText.getLocalBounds();
		m_nameText.setOrigin(textRect2.left + textRect2.width / 2.0f,
			textRect2.top + textRect2.height / 2.0f);
		m_window.draw(m_nameText);
	}

	m_dayCounterText.setString("DAY: " + std::to_string(m_dayCounter) + " (" + std::to_string(m_dayCounter / 365) + " years)");
	const sf::FloatRect textRect = m_dayCounterText.getLocalBounds();
	m_dayCounterText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_window.draw(m_dayCounterText);
}
