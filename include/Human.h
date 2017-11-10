#pragma once

#include <SFML/Graphics.hpp>

class Human
{
public:
	const uint8_t __MAX_CHILDREN = 3;
	const uint8_t __PROCREATION_FAIL_RATE = 10;
	const uint8_t __MIN_AGE_OF_DEATH = 50;
	const uint8_t __MAX_AGE_OF_DEATH = 100;
	const uint8_t __MIN_AGE_TO_PROCREATE = 14;

	const uint16_t __SOCIAL_RADIUS = 50;

	const uint16_t __MALE_DAY_BETWEEN_PROCREATE = 5;
	const uint16_t __FEMALE_DAY_BETWEEN_PROCREATE = 300;

	enum class Gender
	{
		MALE	 = 0b000,
		FEMALE	 = 0b001,
	};

	explicit Human(Human* p_mom = nullptr);
	~Human();

	bool CanProcreate() const;
	Human* Procreate();

	bool IsDead() const { return m_isDead; }

	void SetPosition(const float p_x, const float p_y);

	sf::Vector2f& GetPosition() { return m_position; }

	void DayTick();

private:
	Gender m_gender;

	bool m_isDead;

	uint8_t m_age;
	uint8_t m_ageOfDeath;

	uint16_t m_livingDay;
	uint16_t m_lastProcreateLivingDay;

	sf::Vector2f m_position;

	uint8_t m_childrenCounter;

	Human* m_mom;
	
};