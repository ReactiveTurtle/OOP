#include "Car.h"
#include <map>
#include <vector>

const std::map <int, std::vector <int>> VALID_GEAR_SPEED {
	{-1, {0, 20}},
	{0, {0, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
};
const int MAX_SPEED = 150;
const int MAX_GEAR = 5;

bool CCar::TurnOnEngine()
{
	m_isEngineOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool IsValidSpeedForGear(int speed, int gear)
{
	auto speedRangeIterator = VALID_GEAR_SPEED.find(gear);
	if (speedRangeIterator != VALID_GEAR_SPEED.end())
	{
		std::vector<int> speedRange = speedRangeIterator->second;
		return speedRange[0] <= speed && speed <= speedRange[1];
	}
	return false;
}

bool IsValidDirectionForChangeGear(int newGear, const Direction& currentDirection)
{
	return (newGear == -1 && currentDirection == Direction::Stand) ||
		(newGear == 0) ||
		(newGear == 1 && currentDirection != Direction::Back) ||
		(newGear > 1 && currentDirection == Direction::Forward);
}

bool CCar::SetGear(int gear)
{
	bool canNotSwitchGear = (!m_isEngineOn && gear != 0) ||
		!IsValidSpeedForGear(m_speed, gear) ||
		!IsValidDirectionForChangeGear(gear, m_direction);
	if (canNotSwitchGear)
	{
		m_gear = gear;
	}
	return !canNotSwitchGear;
}

bool CCar::SetSpeed(int speed)
{
	bool canNotChangeSpeed = m_gear == 0 && m_speed < speed ||
		!IsValidSpeedForGear(speed, m_gear);
	if (canNotChangeSpeed)
	{
		return false;
	}
	m_speed = speed;

	if (speed == 0)
	{
		m_direction = Direction::Stand;
	}
	else if (speed > 0 && m_gear == -1)
	{
		m_direction = Direction::Back;
	}
	else if (speed > 0 && m_gear > 0)
	{
		m_direction = Direction::Forward;
	}

	return true;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}
