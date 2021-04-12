#include "Car.h"
#include "CarControl.h"
#include <string>
#include <regex>
#include <iostream>

CCarControl::CCarControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
{
}

bool CCarControl::HandleCommand()
{
	std::string command;
	getline(m_input, command);
	std::regex commandRegex("^ *(\\w+) *(-?\\w*) *$");
	std::smatch urlMatchResult;

	if (!std::regex_match(command, urlMatchResult, commandRegex))
	{
		return false;
	}

	std::transform(command.begin(), command.end(), command.begin(), tolower);
	std::string action = urlMatchResult[1];
	bool wasError = false;

	if (action == "info")
	{
		PrintInfo();
	}
	else if (action == "engineon")
	{
		EngineOn();
	}
	else if (action == "engineoff")
	{
		EngineOff();
	}
	else if (action == "setgear")
	{
		size_t errorPosition;
		std::string mayBeGear = urlMatchResult[2];
		int gear = stoi(mayBeGear, &errorPosition);
		wasError = errorPosition != mayBeGear.length();
		if (!wasError) {
			SetGear(gear);
		}
	}
	else if (action == "setspeed")
	{
		size_t errorPosition;
		std::string mayBeSpeed = urlMatchResult[2];
		int speed = stoi(mayBeSpeed, &errorPosition);
		wasError = errorPosition != mayBeSpeed.length();
		if (!wasError) {
			SetSpeed(speed);
		}
	}

	return !wasError;
}

bool CCarControl::EngineOn()
{
	bool isTurnedOn = m_car.TurnOnEngine();
	if (isTurnedOn)
	{
		m_output << "Engine is on" << std::endl;
	}

	return isTurnedOn;
}

bool CCarControl::EngineOff()
{
	bool isTurnedOff = m_car.TurnOffEngine();
	if (isTurnedOff)
	{
		m_output << "Engine is off" << std::endl;
	}
	else
	{
		m_output << "Failed to turn off engine" << std::endl;
		m_output << "Speed must be 0 and gear must be neutral" << std::endl;
	}

	return isTurnedOff;
}

std::string DirectionToString(const Direction& direction)
{
	switch (direction)
	{
	case Direction::Back:
		return "back";
	case Direction::Stand:
		return "stand";
	case Direction::Forward:
		return "forward";
	default:
		return "Invalid direction";
	}
}

std::string GearToString(int gear)
{
	switch (gear)
	{
	case -1:
		return "reverse";
	case 0:
		return "neutral";
	case 1:
		return "first";
	case 2:
		return "second";
	case 3:
		return "third";
	case 4:
		return "fourth";
	case 5:
		return "fifth";
	default:
		return "Invalid gear";
	}
}

bool CCarControl::PrintInfo()
{
	m_output << "Engine: " << (m_car.IsEngineOn() ? "on" : "off") << std::endl;
	m_output << "Speed: " << m_car.GetSpeed() << std::endl;
	m_output << "Direction: " << DirectionToString(m_car.GetDirection()) << std::endl;
	m_output << "Gear: " << GearToString(m_car.GetGear()) << std::endl;

	return false;
}

bool CCarControl::SetGear(int gear)
{
	bool isGearChanged = m_car.SetGear(gear);
	if (isGearChanged)
	{
		m_output << "Gear is changed to " << GearToString(gear) << std::endl;
	}
	else
	{
		m_output << "Gear did not change" << std::endl;
	}

	return isGearChanged;
}

bool CCarControl::SetSpeed(int speed)
{
	bool isSpeedChanged = m_car.SetSpeed(speed);
	if (isSpeedChanged)
	{
		m_output << "Speed is " << speed << std::endl;
	}
	else
	{
		m_output << "Speed did not change" << std::endl;
	}

	return isSpeedChanged;
}
