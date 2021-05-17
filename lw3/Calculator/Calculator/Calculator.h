#pragma once
#include "Function.h"
#include "Variable.h"
#include <map>
#include <string>
#include <vector>

class Calculator
{
public:
	typedef std::map<std::string, std::optional<double>> Values;

	void DeclareVariable(const std::string& name);

	void SetVariableValue(const std::string& name, double value);
	void SetVariableValue(const std::string& name, const std::string& argName);

	void CreateFunction(const std::string& name, const std::string& argName);
	void CreateFunction(
		const std::string& name,
		const std::string& firstArgName,
		const Function::Operation& operation,
		const std::string& secondArgName);

	Values GetVariableValues() const;
	Values GetFunctionValues() const;
	std::optional<double> GetValue(const std::string& name) const;

private:
	enum class Type
	{
		Variable,
		Function
	};
	std::map<std::string, Variable> m_variables;
	std::map<std::string, Function> m_functions;
	std::vector<std::string> m_functionsInOrder;

	bool VariableExists(const std::string& name) const;
	bool FunctionExists(const std::string& name) const;
	void ThrowIfIdentifierExist(const std::string& name) const;
	void ThrowIfIdentifierNotExist(const std::string& name) const;

	void ApplyFunction(Function& function);

	void UpdateFunctionValues(const std::string& changedVar);
};
