#include "Human.h"

Human::Human(const Gender p_gender)
{
	m_gender = p_gender;

	Init();
}

Human::Human(Human* p_mom)
{
	if (random_between(0, 1) == 0)
		m_gender = Gender::MALE;
	else
		m_gender = Gender::FEMALE;

	m_mom = p_mom;

	Init();
}

Human::~Human()
{
}

void Human::Init()
{
	std::string line;
	std::ifstream* myfile = nullptr;

	if (m_gender == Gender::MALE)
	{
		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 255;
		myfile = new std::ifstream("../config/names/male");
	}
	else if (m_gender == Gender::FEMALE)
	{
		m_color.r = 255;
		m_color.g = 102;
		m_color.b = 204;
		myfile = new std::ifstream("../config/names/female");
	}

	
	if (myfile->is_open())
	{
		int lineCounter = 0;
		while (getline(*myfile, line))
		{
			++lineCounter;
		}

		myfile->clear();
		myfile->seekg(0, std::ios::beg);

		const int randomLine = random_between(1, lineCounter);
		int buff = 1;

		while (getline(*myfile, line))
		{
			if (buff++ == randomLine)
				m_name = line;
		}

		myfile->close();
	}

	delete myfile;

	SetRandomVelocity();

	m_childrenCounter = 0;

	m_age = 0;
	m_ageOfDeath = static_cast<uint8_t>(random_between(__MIN_AGE_OF_DEATH, __MAX_AGE_OF_DEATH));
	m_livingDay = 0;
	m_lastProcreateLivingDay = 0;
	m_isDead = false;

	m_position.x = 0;
	m_position.y = 0;
}

bool Human::CanProcreate() const
{
	bool canProcreate = true;

	int dayBetweenProcreate = 0;

	if (m_gender == Gender::MALE)
		dayBetweenProcreate = __MALE_DAY_BETWEEN_PROCREATE;
	else
		dayBetweenProcreate = __FEMALE_DAY_BETWEEN_PROCREATE;

	const int daySinceLastProcreate = m_livingDay - m_lastProcreateLivingDay;

	if (daySinceLastProcreate < dayBetweenProcreate)
	{
		canProcreate = false;
	}

	if (m_childrenCounter >= __MAX_CHILDREN || m_age < __MIN_AGE_TO_PROCREATE)
	{
		canProcreate = false;
	}

	return canProcreate;
}

Human* Human::Procreate()
{
	if (random_between(1, 100) <= __PROCREATION_FAIL_RATE)
		return nullptr;

	++m_childrenCounter;
	m_lastProcreateLivingDay = m_livingDay;

	if (m_gender == Gender::FEMALE)
		return new Human(this);
	
	return nullptr;
}

void Human::SetPosition(const float p_x, const float p_y)
{
	m_position.x = p_x;
	m_position.y = p_y;
}

void Human::SetRandomVelocity()
{
	do
	{
		m_velocity.x = random_between(0, 2) - 1;
		m_velocity.y = random_between(0, 2) - 1;
	} while (m_velocity.x == 0 && m_velocity.y == 0);
}

bool Human::CanMeet(Human* p_other)
{
	if (p_other && p_other != this)
	{
		return sqrt(pow(m_position.x - p_other->GetPosition().x, 2) + pow(m_position.y - p_other->GetPosition().y, 2)) <= __SOCIAL_RADIUS * 2;
	}

	return false;
}

void Human::Move()
{
	m_position.x += m_velocity.x * (30 - m_age) / 5;
	m_position.y += m_velocity.y * (30 - m_age) / 5;

	if (m_position.x < 0)
	{
		m_position.x = 0;
		m_velocity.x *= -1;
	}

	if (m_position.x > 800)
	{
		m_position.x = 800;
		m_velocity.x *= -1;
	}

	if (m_position.y < 0)
	{
		m_position.y = 0;
		m_velocity.y *= -1;
	}

	if (m_position.y > 800)
	{
		m_position.y = 800;
		m_velocity.y *= -1;
	}
}

void Human::DayTick()
{
	if (!m_isDead)
	{
		++m_livingDay;

		if (m_livingDay % 365 == 0)
		{
			++m_age;
		}

		if (random_between(0, 500) == 0)
			SetRandomVelocity();

		Move();

		if (m_age == m_ageOfDeath)
			m_isDead = true;
	}
}
