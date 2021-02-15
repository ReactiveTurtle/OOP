#include <iostream>
#include <string>

using namespace std;

struct ConvertModel {
	int fromRadix;
	int toRadix;
	string value;
	bool wasError;
	ConvertModel(
		int fromRadix,
		int toRadix,
		string value,
		bool wasError) {
		this->fromRadix = fromRadix;
		this->toRadix = toRadix;
		this->value = value;
		this->wasError = wasError;
	}
};

ConvertModel ValidateAndBuildModel(int argc, char* argv[]);
int ParseInt(string str, bool& wasError);

void End(string result, bool wasError);

string Convert(ConvertModel& convertModel);
int StringToInt(const string& str, int radix, bool& wasError);
string IntToString(int n, int radix, bool& wasError);

int main(int argc, char* argv[])
{
	ConvertModel convertModel = ValidateAndBuildModel(argc, argv);
	string result = "";
	if (!convertModel.wasError) {
		result = Convert(convertModel);
	}
	End(result, convertModel.wasError);
	return 0;
}

ConvertModel ValidateAndBuildModel(int argc, char* argv[]) {
	bool wasError = argc < 4;
	return ConvertModel(
		!wasError ? ParseInt(string(argv[1]), wasError) : 0,
		!wasError ? ParseInt(string(argv[2]), wasError) : 0,
		!wasError ? argv[3] : "",
		wasError);
}

int ParseInt(string str, bool& wasError) {
	if (wasError) {
		return 0;
	}
	try {
		size_t pos;
		int result = stoi(str, &pos);
		if (pos != str.size())
			wasError = true;
		return result;
	}
	catch (exception e) {
		wasError = true;
	}
	return 0;
}

void End(string result, bool wasError) {
	if (wasError) {
		cout << "Error of converting";
	}
	else {
		cout << result;
	}
	cout << endl;
}

string Convert(ConvertModel& convertModel) {
	if (convertModel.value == "0") {
		return "0";
	}
	if (convertModel.fromRadix == 10) {
		int number = ParseInt(convertModel.value, convertModel.wasError);
		return !convertModel.wasError ? IntToString(number, convertModel.toRadix, convertModel.wasError) : "";
	}
	else if (convertModel.toRadix == 10) {
		int decimal = StringToInt(string(convertModel.value), convertModel.fromRadix, convertModel.wasError);
		return !convertModel.wasError ? to_string(decimal) : "";
	}
	else {
		int decimal = StringToInt(string(convertModel.value), convertModel.fromRadix, convertModel.wasError);
		return !convertModel.wasError ? IntToString(decimal, convertModel.toRadix, convertModel.wasError) : "";
	}
}

int StringToInt(const string& str, int radix, bool& wasError) {
	if (radix < 2 || radix > 36) {
		wasError = true;
		return 0;
	}

	bool isNegative = (str[0] == '-');
	if (radix == 2) {
		isNegative = str[0] == '1';
	}
	string strNumber = str;
	if (isNegative) {
		strNumber = strNumber.substr(1);
	}
	int result = 0;
	for (int i = 0; i < strNumber.length() && !wasError; i++) {
		char ch = strNumber[i];
		int chNumber = 0;
		if (ch >= '0' && ch <= '9') {
			chNumber = ch - '0';
		}
		else if (ch >= 'A' && ch <= ('A' + radix - 1)) {
			chNumber = ch - 'A' + 10;
		}
		else if (ch >= 'a' && ch <= ('a' + radix - 1)) {
			chNumber = ch - 'a' + 10;
		}
		else {
			wasError = true;
		}
		result += chNumber * pow(radix, strNumber.length() - i - 1);
		if (result == INT_MAX || result == INT_MIN) {
			wasError = true;
		}
	}

	if (wasError) {
		return 0;
	}

	if (isNegative) {
		result = -result;
	}
	return result;
}

char IntToChar(int number) {
	if (number >= 0 && number <= 9) {
		return to_string(number)[0];
	}
	else {
		char symbol = 'A' + number - 10;
		return symbol;
	}
}

string IntToString(int n, int radix, bool& wasError) {
	if (radix < 2 || radix > 36) {
		wasError = true;
		return "";
	}
	int number = abs(n);
	string result;
	while (number >= radix) {
		int mod = number % radix;
		number /= radix;
		result = IntToChar(mod) + result;
	}
	result = IntToChar(number) + result;
	string sign = "";
	if (n < 0) {
		sign = (radix == 2 ? "1" : "-");
	}
	else if (radix == 2) {
		sign = "0";
	}
	result = sign + result;
	return result;
}
