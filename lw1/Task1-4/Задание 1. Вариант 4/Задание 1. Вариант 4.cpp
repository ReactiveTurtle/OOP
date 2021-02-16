#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 5 ||
		string(argv[1]) == "" || string(argv[2]) == "") {
		cout << "****Error****" << endl;
		return 0;
	}
	ifstream input(argv[1]);
	if (!input.is_open()) {
		return 0;
	}
	ofstream output(argv[2]);
	if (!output.is_open()) {
		return 0;
	}

	string searchStr = argv[3];
	int searchStrLength = searchStr.length();
	string replaceStr = argv[4];
	string buffer;
	while (getline(input, buffer)) {
		int pos = 0;
		while (searchStr != "" && (pos = buffer.find(searchStr)) > -1) {
			string newStr = buffer.substr(0, pos) + replaceStr;
			output << newStr;
			buffer = buffer.substr(pos + searchStr.length());
		}
		output << buffer << endl;
	}
	input.close();
	output.close();
	return 0;
}
