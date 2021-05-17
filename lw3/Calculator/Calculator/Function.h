#pragma once
#include <string>
#include <optional>

class Function
{
public:
	enum class Operation
	{
		Add,
		Sub,
		Div,
		Mul,
		Nothing
	};
	Function(const std::string& argName = "");
	Function(const std::string& firstArgName, const Operation& operation, const std::string& secondArgName);

	std::optional<double> Apply();

	void SetValue(std::optional<double> value);

	std::optional<double> GetValue() const;
	std::string GetFirstArgName() const;
	std::string GetSecondArgName() const;
	Operation GetOperation() const;

private:
	std::string m_firstArgName;
	std::string m_secondArgName;
	Operation m_operation;
	std::optional<double> m_value;
};
