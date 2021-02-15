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
		return 0;
	}
	ifstream input(argv[1]);
	if (!input.is_open()) {
		return 0;
	}
	ofstream output(argv[2]);

	string searchStr = argv[3];
	int searchStrLength = searchStr.length();
	string replaceStr = argv[4];
	string buffer;
	bool isFirst = true;
	while (getline(input, buffer)) {
		if (isFirst) {
			isFirst = false;
		}
		else {
			output << endl;
		}
		int pos = 0;
		while ((pos = buffer.find(searchStr)) > -1) {
			output << buffer.substr(0, pos) << replaceStr;
			buffer = buffer.substr(pos + searchStr.length());
		}
		output << buffer;
	}
	input.close();
	output.close();
	return 0;
}
