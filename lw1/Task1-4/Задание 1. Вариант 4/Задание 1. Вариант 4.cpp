#include <iostream>
#include <fstream>
#include <string>
#include <optional>
using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

Args ParseArgs(int argc, char* argv[], bool& wasError);
bool Replace(string inputFileName, string outputFileName, string searchStr, string replaceStr);

int main(int argc, char* argv[])
{
	bool wasError = false;
	Args args = ParseArgs(argc, argv, wasError);
	if (wasError) {
		return 1;
	}

	if (!Replace(args.inputFileName, args.outputFileName, args.searchString, args.replaceString))\
	{
		return 1;
	}

	return 0;
}

Args ParseArgs(int argc, char* argv[], bool& wasError)
{
	Args args;
	if (argc < 5)
	{
		wasError = true;
	}

	args.inputFileName = argv[0];
	args.outputFileName = argv[1];
	args.searchString = argv[2];
	args.replaceString = argv[3];
	return args;
}

bool Replace(string inputFileName, string outputFileName, string searchString, string replaceString)
{
	ifstream input(inputFileName);
	if (!input.is_open())
	{
		return false;
	}
	ofstream output(outputFileName);
	if (!output.is_open())
	{
		return false;
	}

	string buffer;
	size_t searchStrLength = searchString.length();
	while (getline(input, buffer))
	{
		size_t pos = 0;
		size_t foundPos = 0;
		while (searchString != "" && (foundPos = buffer.find(searchString, pos)) != string::npos)
		{
			if (!output.flush())
			{
				return false;
			}
			for (int i = pos; i < foundPos; i++)
			{
				output << buffer[i];
			}
			output << replaceString;
			pos = foundPos + searchStrLength;
		}
		if (!output.flush())
		{
			return false;
		}
		for (int i = pos; i < buffer.length(); i++)
		{
			output << buffer[i];
		}
		output << endl;
	}
	input.close();
	output.close();
	return true;
}
