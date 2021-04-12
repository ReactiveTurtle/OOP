#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task1-1-Car/Car.h"

SCENARIO("Car to max gear and speed and stop")
{
	CCar car;
	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.SetGear(3));
	REQUIRE(!car.SetSpeed(70));
	REQUIRE(car.SetSpeed(60));
	REQUIRE(car.SetGear(5));
	REQUIRE(car.SetSpeed(150));
	REQUIRE(!car.SetSpeed(151));

	REQUIRE(car.SetGear(0));
	REQUIRE(car.SetSpeed(0));
}