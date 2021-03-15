#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Args
{
	string command;
	string inputPath;
	string outputPath;
	unsigned char key;
};

Args ParseArgs(int argc, char* argv[], bool& wasError);
void Crypt(ifstream& input, ofstream& output, unsigned char key);
void Decrypt(ifstream& input, ofstream& output, unsigned char key);
string ToLowerCase(string str);

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cout << "You must be enter 5 arguments. Input notation must be: <Program> <crypt or decrypt> <input> <output> <byte key>" << endl;
		return 1;
	}
	bool wasError;
	Args args = ParseArgs(argc, argv, wasError);
	if (wasError) {
		cout << "Invalid byte key" << endl;
		return 1;
	}
	ifstream input(args.inputPath, ios::binary);
	if (!input.is_open())
	{
		cout << "Input file not found" << endl;
		return 1;
	}
	ofstream output(args.outputPath, ios::binary);
	if (!output.is_open())
	{
		cout << "Output file open error" << endl;
		return 1;
	}

	string command = ToLowerCase(args.command);
	if (command == "crypt")
	{
		Crypt(input, output, args.key);
	}
	else if (command == "decrypt")
	{
		Decrypt(input, output, key);
	}
	else
	{
		cout << "Invalid command. Second argument must be 'crypt' or 'decrypt'" << endl;
		return 1;
	}
	input.close();
	output.close();
}

Args ParseArgs(int argc, char* argv[], bool& wasError)
{
	Args args;
	wasError = argc < 5;
	if (wasError)
	{
		return args;
	}
	args.command = argv[1];
	args.inputPath = argv[2];
	args.outputPath = argv[3];

	size_t errorPos;
	int mayBeKey = stoi(string(argv[4]), &errorPos);
	wasError = errorPos != string(argv[4]).size() || (mayBeKey < 0 || mayBeKey > 255);
	if (!wasError)
	{
		unsigned char key = mayBeKey;
	}

	return args;
}

char CharToLowerCase(char in)
{
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

string ToLowerCase(string str)
{
	string result = str;
	size_t size = str.length();
	for (int i = 0; i < size; i++)
	{
		result[i] = CharToLowerCase(str[i]);
	}
	return result;
}

void Crypt(ifstream& input, ofstream& output, unsigned char key)
{
	unsigned char byte;
	while (!input.eof())
	{
		byte = input.get();
		if (input.eof())
		{
			break;
		}
		if (byte == '\r' || byte == '\n')
		{
			output << byte;
			continue;
		}
		unsigned char combined = byte ^ key;
		unsigned char bit76 = (unsigned char)(combined >> 3) << 6;
		unsigned char bit5 = (unsigned char)(combined >> 7) << 5;
		unsigned char bit432 = (unsigned char)(combined << 5) >> 3;
		unsigned char bit10 = (unsigned char)(combined << 1) >> 6;
		unsigned char crypted = bit76 + bit5 + bit432 + bit10;
		output << crypted;
	}
}

void Decrypt(ifstream& input, ofstream& output, unsigned char key)
{
	unsigned char byte;
	while (!input.eof())
	{
		byte = input.get();
		if (input.eof())
		{
			break;
		}
		if (byte == '\r' || byte == '\n')
		{
			output << byte;
			continue;
		}
		unsigned char bit7 = (unsigned char)(byte >> 5) << 7;
		unsigned char bit65 = (unsigned char)(byte << 6) >> 1;
		unsigned char bit43 = (unsigned char)(byte >> 6) << 3;
		unsigned char bit210 = (unsigned char)(byte << 3) >> 5;
		unsigned char decrypted = bit7 | bit65 | bit43 | bit210;
		unsigned char uncombined = decrypted ^ key;
		output << uncombined;
	}
}
