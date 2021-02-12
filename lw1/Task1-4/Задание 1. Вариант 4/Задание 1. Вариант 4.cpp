#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool ValidateInputArgs(int argc, char* argv[]) {
	if (argc < 5) {
		return false;
	}
	string args[5] = { argv[0], argv[1], argv[2], argv[3], argv[4] };
	if (args[1] == "" || args[2] == "" ||
		args[3] == "" || args[4] == "") {
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (!ValidateInputArgs(argc, argv)) {
		return 1;
	}
	ifstream input(argv[1]);
	cout << "'" << argv[2] << "'" << endl;
	if (!input.is_open()) {
		return 1;
	}
	ofstream output(argv[2]);

	string searchStr = argv[3];
	int searchStrLength = searchStr.length();
	string replaceStr = argv[4];
	string buffer;
	while (getline(input, buffer)) {
		int pos = 0;
		string newLine;
		while ((pos = buffer.find(searchStr)) > -1) {
			newLine += buffer.substr(0, pos) + replaceStr;
			buffer = buffer.substr(pos + searchStr.length());
		}
		newLine += buffer;
		output << newLine << endl;
	}
	input.close();
	output.close();
	return 0;
}
