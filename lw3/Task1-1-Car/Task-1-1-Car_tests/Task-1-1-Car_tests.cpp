#include "../../../catch2/catch.hpp"
#include "../Task1-1-Car/Car.h"

TEST_CASE("Car set speed when engine off")
{
	CCar car;
	REQUIRE(!car.SetSpeed(30));
}

TEST_CASE("Car to max gear and speed and stop")
{
	CCar car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(1));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.GetSpeed() == 0);

	REQUIRE(car.SetSpeed(30));
	REQUIRE(car.GetGear() == 1);
	REQUIRE(car.GetSpeed() == 30);

	REQUIRE(car.SetGear(3));
	REQUIRE(car.GetGear() == 3);
	REQUIRE(car.GetSpeed() == 30);

	REQUIRE(!car.SetSpeed(70));
	REQUIRE(car.GetGear() == 3);
	REQUIRE(car.GetSpeed() == 30);

	REQUIRE(car.SetSpeed(60));
	REQUIRE(car.GetGear() == 3);
	REQUIRE(car.GetSpeed() == 60);

	REQUIRE(car.SetGear(5));
	REQUIRE(car.GetGear() == 5);
	REQUIRE(car.GetSpeed() == 60);
	
	REQUIRE(car.SetSpeed(150));
	REQUIRE(car.GetGear() == 5);
	REQUIRE(car.GetSpeed() == 150);

	REQUIRE(!car.SetSpeed(151));
	REQUIRE(car.GetGear() == 5);
	REQUIRE(car.GetSpeed() == 150);

	REQUIRE(car.SetGear(0));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 150);

	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);

	REQUIRE(car.TurnOffEngine());
	REQUIRE(!car.IsEngineOn());
}

TEST_CASE("Car set gear back")
{
	CCar car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(-1));
	REQUIRE(car.SetSpeed(20));
	REQUIRE(car.SetGear(0));
	REQUIRE(car.SetSpeed(0));
	REQUIRE(car.TurnOffEngine());
}

TEST_CASE("Car set back gear back when speed greater than 0")
{
	CCar car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(car.SetGear(1));
	REQUIRE(car.SetSpeed(30));
	REQUIRE(!car.SetGear(-1));
}

TEST_CASE("Car set very high gear")
{
	CCar car;
	REQUIRE(car.TurnOnEngine());
	REQUIRE(!car.SetGear(5));
}
