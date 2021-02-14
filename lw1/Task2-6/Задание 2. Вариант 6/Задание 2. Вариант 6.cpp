#include <iostream>
#include <string>

using namespace std;

int StringToInt(const string& str, int radix, bool& wasError);
string IntToString(int n, int radix, bool& wasError);

bool IsArgsEmpty(int argc, char* argv[]) {
	if (argc < 4) {
		return false;
	}
	string args[] = { argv[0], argv[1], argv[2], argv[3] };
	if (args[1] == "" || args[2] == "" || args[3] == "") {
		return false;
	}
	return true;
}

int ParseInt(string str, bool& wasError) {
	size_t pos;
	try {
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

string Convert(int src, int dst, string numberStr, bool& wasError) {
	if (src == 10) {
		int number = ParseInt(numberStr, wasError);
		return !wasError ? IntToString(number, dst, wasError) : "";
	}
	else if (dst == 10) {
		return to_string(StringToInt(numberStr, src, wasError));
	}
	else {
		int decimal = StringToInt(numberStr, src, wasError);
		return !wasError ? IntToString(decimal, dst, wasError) : 0;
	}
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

int main(int argc, char* argv[])
{
	if (!IsArgsEmpty(argc, argv)) {
		cout << "Empty args" << endl;
		return 0;
	}
	bool wasError = false;
	string result;
	if (!wasError) {
		int src = ParseInt(string(argv[1]), wasError);
		if (wasError) {
			End(result, wasError);
			return 0;
		}
		int dst = ParseInt(string(argv[2]), wasError);
		if (wasError) {
			End(result, wasError);
			return 0;
		}

		string numberStr = argv[3];
		result = Convert(src, dst, numberStr, wasError);
	}
	End(result, wasError);
	return 0;
}

int StringToInt(const string& str, int radix, bool& wasError) {
	if (radix < 2 || radix > 36) {
		wasError = true;
		return 0;
	}

	bool isNegative = str[0] == '-';
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
	if (n < 0) {
		result = "-" + result;
	}
	return result;
}
