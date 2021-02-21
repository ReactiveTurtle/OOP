#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Crypt(ifstream& input, ofstream& output, unsigned char key);
void Decrypt(ifstream& input, ofstream& output, unsigned char key);

int main(int argc, char* argv[])
{
	if (argc < 5) {
		cout << "Error" << endl;
		return 0;
	}
	ifstream input(argv[2], ios::binary);
	if (!input.is_open()) {
		cout << "Error" << endl;
		return 0;
	}
	ofstream output(argv[3], ios::binary);
	if (!output.is_open()) {
		cout << "Error" << endl;
		return 0;
	}

	size_t errorPos;
	int mayBeKey = stoi(string(argv[4]), &errorPos);
	if (errorPos != string(argv[4]).size() || (mayBeKey < 0 || mayBeKey > 255)) {
		cout << "Error" << endl;
		return 0;
	}
	unsigned char key = mayBeKey;

	string command = argv[1];
	if (command == "crypt") {
		Crypt(input, output, key);
	}
	else if (command == "decrypt") {
		Decrypt(input, output, key);
	}
	else {
		cout << "Error" << endl;
		return 0;
	}
	input.close();
	output.close();
}

void Crypt(ifstream& input, ofstream& output, unsigned char key) {
	unsigned char byte;
	while (!input.eof()) {
		byte = input.get();
		if (input.eof()) {
			break;
		}
		if (byte == '\r' || byte == '\n') {
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

void Decrypt(ifstream& input, ofstream& output, unsigned char key) {
	unsigned char byte;
	while (!input.eof()) {
		byte = input.get();
		if (input.eof()) {
			break;
		}
		if (byte == '\r' || byte == '\n') {
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
