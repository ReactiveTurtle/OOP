#include <sstream>
#include <string>
#include "../../../catch2/catch.hpp"
#include "../Task1-1-Car/Car.h"
#include "../Task1-1-Car/CarControl.h"

using namespace std;

TEST_CASE("Check engine on")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	carControl.HandleCommand();
	input << "engineon" << endl;
	string answer;
	getline(output, answer);
	REQUIRE(answer == "Engine is on\n");
}

TEST_CASE("Check engine off")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	carControl.HandleCommand();
	input << "engineon" << endl;
	string answer;
	getline(output, answer);
	input << "engineoff" << endl;
	getline(output, answer);
	REQUIRE(answer == "Engine is off\n");
}

TEST_CASE("Check set valid gear")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	carControl.HandleCommand();
	input << "engineon" << endl;
	string answer;
	getline(output, answer);
	input << "setgear 1" << endl;
	getline(output, answer);
	REQUIRE(answer == "Gear is changed to 1\n");
}

TEST_CASE("Check set invalid gear")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	carControl.HandleCommand();
	input << "engineon" << endl;
	string answer;
	getline(output, answer);
	input << "setgear 2" << endl;
	getline(output, answer);
	REQUIRE(answer == "Gear did not change\n");
}

TEST_CASE("Check set valid speed")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	carControl.HandleCommand();
	string answer;
	input << "engineon" << endl;
	getline(output, answer);
	input << "setgear 1" << endl;
	getline(output, answer);
	input << "setspeed 30" << endl;
	getline(output, answer);
	REQUIRE(answer == "Speed is changed to 30\n");
}

TEST_CASE("Check set invalid speed")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	carControl.HandleCommand();
	string answer;
	input << "engineon" << endl;
	getline(output, answer);
	input << "setgear 1" << endl;
	getline(output, answer);
	input << "setspeed 40" << endl;
	getline(output, answer);
	REQUIRE(answer == "Speed did not change\n");
}

TEST_CASE("Check info")
{
	CCar car;
	stringstream input;
	stringstream output;
	CCarControl carControl(car, input, output);

	string answer;
	input << "info" << endl;
	getline(output, answer);
	output >> answer;
	carControl.HandleCommand();
	REQUIRE(answer == "Speed did not change\n");
}
