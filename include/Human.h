#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Util.h"


class Human
{
public:
	const uint8_t __MAX_CHILDREN = 3;
	const uint8_t __PROCREATION_FAIL_RATE = 25;
	const uint8_t __MIN_AGE_OF_DEATH = 8;
	const uint8_t __MAX_AGE_OF_DEATH = 12;
	const uint8_t __MIN_AGE_TO_PROCREATE = 2;
	const uint16_t __DESEASE_RATE = 3600;

	const uint16_t __SOCIAL_RADIUS = 20;

	const uint16_t __MALE_DAY_BETWEEN_PROCREATE = 200;
	const uint16_t __FEMALE_DAY_BETWEEN_PROCREATE = 700;

	enum class Gender
	{
		MALE	 = 0b000,
		FEMALE	 = 0b001,
	};

	explicit Human(const Gender p_gender);
	explicit Human(Human* p_mom = nullptr);
	~Human();

	void Init();

	bool CanProcreate() const;
	bool CanMeet(Human* p_other);
	bool IsDead() const { return m_isDead; }

	sf::Color& GetColor() { return m_color; }
	uint8_t GetAge() const { return m_age; }
	sf::Vector2f& GetPosition() { return m_position; }
	Gender GetGender() const { return m_gender; }
	std::string& GetName() { return m_name; }

	void SetPosition(const float p_x, const float p_y);
	void SetRandomVelocity();
	void SetName(const std::string p_name) { m_name = p_name; }

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

	std::string m_name;

	uint8_t m_childrenCounter;

	Human* m_mom;
	
};