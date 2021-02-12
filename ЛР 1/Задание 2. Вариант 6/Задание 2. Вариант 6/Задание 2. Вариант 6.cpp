// Задание 2. Вариант 6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

int StringToInt(const string& str, int radix, bool& wasError);
string IntToString(int n, int radix, bool& wasError);

bool ValidateInputArgs(int argc, char* argv[]) {
	if (argc < 4) {
		return false;
	}
	string args[] = { argv[0], argv[1], argv[2], argv[3] };
	if (args[1] == "" || args[2] == "" || args[3] == "") {
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!ValidateInputArgs(argc, argv)) {
		return 1;
	}
	int src = stoi(string(argv[1]));
	int dst = stoi(string(argv[2]));
	string numberStr = argv[3];
	if (src == 10) {
		bool wasError = false;
		int number = stoi(numberStr);
		string result = IntToString(number, dst, wasError);
		cout << result << endl;
	}
	else if (dst == 10) {
		bool wasError = false;
		cout << StringToInt(numberStr, dst, wasError);
	}
	else {
		bool wasError = false;
		int decimal = StringToInt(numberStr, 10, wasError);
		cout << IntToString(decimal, dst, wasError);
	}
	cout << endl;
	return 0;
}

int StringToInt(const string& str, int radix, bool& wasError) {
	bool isNegative = str[0] == '-';
	string strNumber = str;
	if (isNegative) {
		strNumber = strNumber.substr(1);
	}
	int result = 0;
	for (int i = 0; i < strNumber.length(); i++) {
		char ch = strNumber[i];
		int chNumber = 0;
		if (ch >= '0' && ch <= '9') {
			chNumber = ch - '0';
		}
		else if (ch >= 'A' && ch <= 'Z') {
			chNumber = ch - 'A' + 10;
		}
		else if (ch >= 'a' && ch <= 'z') {
			chNumber = ch - 'a' + 10;
		}
		result += chNumber * pow(radix, strNumber.length() - i - 1);
	}
	if (isNegative) {
		result = -result;
	}
	return result;
}

string IntToString(int n, int radix, bool& wasError) {
	int number = abs(n);
	string result;
	while (number >= radix) {
		int mod = number % radix;
		number /= radix;
		if (number >= 0 && number <= 9) {
			result = number + "" + result;
		}
		else {
			result = 'A' + "" + (mod - 10) + result;
		}
	}
	if (n < 0) {
		result = "-" + result;
	}
	return result;
}
