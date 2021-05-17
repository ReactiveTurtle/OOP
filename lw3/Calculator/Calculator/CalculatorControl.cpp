#include "CalculatorControl.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <iomanip> 

CalculatorControl::CalculatorControl(Calculator& calc, std::istream& input, std::ostream& output)
	: m_calc(calc)
	, m_input(input)
	, m_output(output)
{
}

struct LetArgs
{
	std::string identifier;
	std::string value;
};

struct FunctionArgs
{
	std::string identifier;
	std::string firstArg;
	std::string operation;
	std::string secondArg;
};

bool CalculatorControl::StartHandler()
{
	try
	{
		if (!HandleCommand())
		{
			return false;
		}
	}
	catch (const std::runtime_error& error)
	{
		m_output << error.what() << std::endl;
	}
	return true;
}

bool CalculatorControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);

	std::smatch matches;
	std::regex regex("^ *(\\w+) *(.*) *$");
	if (!std::regex_match(commandLine, matches, regex))
	{
		return false;
	}

	std::string command = matches[1];
	if (command == "var")
	{
		std::string identifier = matches[2];
		Var(identifier);
	}
	else if (command == "let")
	{
		std::string action = matches[2];
		Let(action);
	}
	else if (command == "fn")
	{
		std::string action = matches[2];
		Function(action);
	}
	else if (command == "print")
	{
		std::string identifier = matches[2];
		Print(identifier);
	}
	else if (command == "printvars")
	{
		PrintVars();
	}
	else if (command == "printfns")
	{
		PrintFunctions();
	}
	else
	{
		return false;
	}

	return true;
}

Function::Operation ToOperation(const std::string& operation)
{
	if (operation == "+")
	{
		return Function::Operation::Add;
	}
	if (operation == "-")
	{
		return Function::Operation::Sub;
	}
	if (operation == "*")
	{
		return Function::Operation::Mul;
	}
	if (operation == "/")
	{
		return Function::Operation::Div;
	}
	return Function::Operation::Nothing;
}

bool IsValidIdentifier(const std::string& identifier)
{
	std::smatch matches;
	std::regex regex("^[a-zA-Z]+\\w*$");
	std::regex_search(identifier, matches, regex);

	if (matches.empty())
	{
		return false;
	}
	return true;
}

void CheckIdentifier(const std::string& name)
{
	if (!IsValidIdentifier(name))
	{
		throw std::runtime_error("Invalid identifier name");
	}
}

void CalculatorControl::Var(const std::string& identifier)
{
	CheckIdentifier(identifier);
	m_calc.DeclareVariable(identifier);
}

std::optional<LetArgs> ParseLet(const std::string& action) {
	std::smatch matches;
	std::regex regex("^([a-zA-Z]+\\w*) *= *([0-9]*.[0-9]*|\\w*)$");
	std::regex_search(action, matches, regex);

	if (matches.empty())
	{
		return std::nullopt;
	}
	LetArgs args;
	args.identifier = matches[1];
	args.value = matches[2];
	return args;
}

void CalculatorControl::Let(const std::string& action)
{
	std::optional<LetArgs> letArgs = ParseLet(action);
	if (!letArgs)
	{
		throw std::runtime_error("Invalid command");
	}
	std::string identifier = letArgs.value().identifier;
	std::string firstArgName = letArgs.value().value;

	CheckIdentifier(identifier);
	
	std::istringstream ss(firstArgName);
	double value;
	if (ss >> value && ss.eof())
	{
		m_calc.SetVariableValue(identifier, value);
	}
	else
	{
		m_calc.SetVariableValue(identifier, firstArgName);
	}
}

std::optional<FunctionArgs> ParseFunction(const std::string& action) {
	std::smatch matches;
	std::regex regex("^([a-zA-Z]+\\w*) *= *([a-zA-Z]+\\w*) *((\\+|-|\\*|/) *([a-zA-Z]+\\w*))*$");
	std::regex_search(action, matches, regex);

	if (matches.empty())
	{
		return std::nullopt;
	}
	FunctionArgs args;
	args.identifier = matches[1];
	args.firstArg = matches[2];
	args.operation = matches[4];
	args.secondArg = matches[5];
	return args;
}

void CalculatorControl::Function(const std::string& action)
{
	std::optional<FunctionArgs> args = ParseFunction(action);
	if (!args)
	{
		throw std::runtime_error("Invalid command");
	}
	std::string identifier = args.value().identifier;
	std::string firstArgName = args.value().firstArg;
	std::string secondArgName = args.value().secondArg;
	Function::Operation operation = ToOperation(args.value().operation);

	CheckIdentifier(identifier);

	if (operation != Function::Operation::Nothing)
	{
		m_calc.CreateFunction(identifier, firstArgName, operation, secondArgName);
	}
	else
	{
		m_calc.CreateFunction(identifier, firstArgName);
	}
}

void CalculatorControl::PrintValue(std::optional<double> value)
{
	if (value)
	{
		m_output << std::fixed << std::setprecision(2);
		m_output << value.value() << std::endl;
	}
	else
	{
		m_output << "NaN" << std::endl;
	}
}
void CalculatorControl::Print(const std::string& identifier)
{
	CheckIdentifier(identifier);
	std::optional<double> value = m_calc.GetValue(identifier);
	PrintValue(value);
}

void CalculatorControl::PrintVars()
{
	Calculator::Values values = m_calc.GetVariableValues();
	for (const auto& [name, value] : values)
	{
		m_output << name << ":";
		PrintValue(value);
	}
}

void CalculatorControl::PrintFunctions()
{
	Calculator::Values values = m_calc.GetFunctionValues();
	for (const auto& [name, value] : values)
	{
		m_output << name << ":";
		PrintValue(value);
	}
}
