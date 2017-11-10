#include "Human.h"
#include "Util.h"

Human::Human(Human* p_mom)
{

	switch (random_between(0, 1))
	{
	case 0:
		m_gender = Gender::MALE;
		break;

	case 1:
		m_gender = Gender::FEMALE;

	default:
		m_gender = Gender::MALE;
		break;
	}

	m_childrenCounter = 0;

	m_mom = p_mom;
	m_age = 0;
	m_ageOfDeath = static_cast<uint8_t>(random_between(__MIN_AGE_OF_DEATH, __MAX_AGE_OF_DEATH));
	m_livingDay = 0;
	m_lastProcreateLivingDay = 0;
	m_isDead = false;

	m_position.x = 0;
	m_position.y = 0;
}

Human::~Human()
{
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

	Human* child;
	if (m_gender == Gender::FEMALE)
		child = new Human(this);
	else
		child = new Human;

	return child;
}

void Human::SetPosition(const float p_x, const float p_y)
{
	m_position.x = p_x;
	m_position.y = p_y;
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

		if (m_age == m_ageOfDeath)
			m_isDead = true;
	}
}
