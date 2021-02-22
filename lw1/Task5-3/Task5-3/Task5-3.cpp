#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void CopyToOutput(ifstream& input, ofstream& output, vector<vector<int>>& points);
void Fill(fstream& output, vector<vector<int>>& points);

int main(int argc, char* argv[])
{
	if (argc < 3) {
		cout << "Error" << endl;
		return 0;
	}
	ifstream input(argv[1]);
	if (!input.is_open()) {
		cout << "Error" << endl;
		return 0;
	}

	ofstream output(argv[2]);
	if (!output.is_open()) {
		cout << "Error" << endl;
		return 0;
	}

	vector<vector<int>> points(0);
	CopyToOutput(input, output, points);
	fstream result(argv[2], ios::in | ios::out);
	Fill(result, points);
}

void CopyToOutput(ifstream& input, ofstream& output, vector<vector<int>>& points) {
	string buffer;
	for (int i = 0; i < 100; i++) {
		if (!getline(input, buffer)) {
			buffer = "";
		}
		int bufferSize = buffer.size();
		for (int j = 0; j < bufferSize && j < 100; j++) {
			output << buffer[j];
			if (buffer[j] == 'O') {
				vector<int> point(2);
				point[0] = j;
				point[1] = i;
				points.push_back(point);
			}
		}
		for (int j = bufferSize; j < 100; j++) {
			output << ' ';
		}
		output << endl;
	}
}

std::fstream& gotoLine(fstream& file, unsigned int num, bool isSeekg) {
	if (isSeekg) {
		file.seekg(std::ios::beg);
	}
	else {
		file.seekp(std::ios::beg);
	}
	for (int i = 0; i < num; ++i) {
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return file;
}

bool IsInRange(int number) {
	return number >= 0 && number < 100;
}

void Fill(fstream& output, vector<vector<int>>& points) {
	for (int i = 0; i < points.size(); i++) {
		vector<int> point = points[i];
		vector<vector<int>> fillPoints(0);
		fillPoints.push_back(point);
		while (fillPoints.size() > 0) {
			vector<int> fillPoint = fillPoints[0];
			int x = fillPoint[0];
			int y = fillPoint[1];
			fillPoints.erase(fillPoints.begin());
			gotoLine(output, y, true);
			output.seekg(x, ios::cur);
			char ch;
			output.get(ch);
			if (ch == ' ') {
				gotoLine(output, y, false);
				output.seekp(x, ios::cur);
				output.put('.');
			}
			if (ch == 'O' || ch == ' ') {
				if (IsInRange(x - 1)) {
					gotoLine(output, y, true);
					output.seekg(x - 1, ios::cur);
					output.get(ch);
					if (ch == ' ') {
						vector<int> newPoint(2);
						newPoint[0] = x - 1;
						newPoint[1] = y;
						fillPoints.push_back(newPoint);
					}
				}
				if (IsInRange(x + 1)) {
					gotoLine(output, y, true);
					output.seekg(x + 1, ios::cur);
					output.get(ch);
					if (ch == ' ') {
						vector<int> newPoint(2);
						newPoint[0] = x + 1;
						newPoint[1] = y;
						fillPoints.push_back(newPoint);
					}
				}
				if (IsInRange(y - 1)) {
					gotoLine(output, y - 1, true);
					output.seekg(x, ios::cur);
					output.get(ch);
					if (ch == ' ') {
						vector<int> newPoint(2);
						newPoint[0] = x;
						newPoint[1] = y - 1;
						fillPoints.push_back(newPoint);
					}
				}
				if (IsInRange(y + 1)) {
					gotoLine(output, y + 1, true);
					output.seekg(x, ios::cur);
					output.get(ch);
					if (ch == ' ') {
						vector<int> newPoint(2);
						newPoint[0] = x;
						newPoint[1] = y + 1;
						fillPoints.push_back(newPoint);
					}
				}
			}
		}
	}
}
