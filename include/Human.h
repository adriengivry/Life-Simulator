#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Util.h"


class Human
{
public:
	const uint8_t __MAX_CHILDREN = 4;
	const uint8_t __PROCREATION_FAIL_RATE = 5;
	const uint8_t __MIN_AGE_OF_DEATH = 5;
	const uint8_t __MAX_AGE_OF_DEATH = 7;
	const uint8_t __MIN_AGE_TO_PROCREATE = 2;

	const uint16_t __SOCIAL_RADIUS = 15;

	const uint16_t __MALE_DAY_BETWEEN_PROCREATE = 30;
	const uint16_t __FEMALE_DAY_BETWEEN_PROCREATE = 250;

	enum class Gender
	{
		MALE	 = 0b000,
		FEMALE	 = 0b001,
	};

	explicit Human(Human* p_mom = nullptr);
	~Human();

	bool CanProcreate() const;
	bool CanMeet(Human* p_other);
	bool IsDead() const { return m_isDead; }


	sf::Color& GetColor() { return m_color; }
	uint8_t GetAge() const { return m_age; }
	sf::Vector2f& GetPosition() { return m_position; }
	Gender GetGender() const { return m_gender; }

	void SetPosition(const float p_x, const float p_y);
	void SetRandomVelocity();

	Human* Procreate();
	void Move();
	void DayTick();

private:
	Gender m_gender;

	bool m_isDead;

	sf::Color m_color;

	uint8_t m_age;
	uint8_t m_ageOfDeath;

	uint16_t m_livingDay;
	uint16_t m_lastProcreateLivingDay;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	uint8_t m_childrenCounter;

	Human* m_mom;
	
};