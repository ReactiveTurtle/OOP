#include <string>
#include <iostream>
#include <fstream>
using namespace std;

float** GetEmptyMatrix();
float** ParseMatrixInput(ifstream& input, bool& wasError);
float** Inverse(float** matrix, bool& wasError);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Invalid input file" << endl;
		return 0;
	}
	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Invalid input file" << endl;
		return 0;
	}
	bool wasError = false;
	
	float** matrix = ParseMatrixInput(input, wasError);
	if (wasError) 
	{
		cout << "Invalid input file" << endl;
		return 0;
	}

	float** inverseMatrix = Inverse(matrix, wasError);
	if (wasError)
	{
		cout << "The matrix is degenerate" << endl;
		return 0;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float buffer = inverseMatrix[i][j];
			cout << buffer << (j == 2 ? "" : " ");
		}
		cout << endl;
	}
	return 0;
}

string Clear(string str)
{
	string result = "";
	bool isFirstNotSpaceFound = false;
	size_t length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (isFirstNotSpaceFound)
		{
			if (str[i] != ' ')
			{
				if (i - 1 > -1 && str[(size_t)i - 1] == ' ')
				{
					result += ' ';
				}
				result += str[i];
			}
		}
		else if (str[i] != ' ') 
		{
			result += str[i];
			isFirstNotSpaceFound = true;
		}
	}
	return result;
}

float** ParseMatrixInput(ifstream& input, bool& wasError)
{
	float** matrix = GetEmptyMatrix();
	string buffer;
	for (int i = 0; i < 3 && !wasError; i++) 
	{
		if (!getline(input, buffer))
		{
			wasError = true;
		}
		else 
		{
			try 
			{
				buffer = Clear(buffer);
				size_t errorPos;

				size_t firstNumberEnd = buffer.find(' ');
				string firstNumberStr = buffer.substr(0, firstNumberEnd);
				buffer = buffer.substr((size_t)firstNumberEnd + 1);
				float first = stof(firstNumberStr, &errorPos);
				if (errorPos != firstNumberStr.size()) 
				{
					wasError = true;
					return matrix;
				}
				matrix[i][0] = first;

				size_t secondNumberEnd = buffer.find(' ');
				string secondNumberStr = buffer.substr(0, secondNumberEnd);
				float second = stof(secondNumberStr, &errorPos);
				if (errorPos != secondNumberStr.size())
				{
					wasError = true;
					return matrix;
				}
				matrix[i][1] = second;

				string thirdNumberStr = buffer.substr(secondNumberEnd + 1);
				float third = stof(thirdNumberStr, &errorPos);
				if (errorPos != thirdNumberStr.size()) 
				{
					wasError = true;
					return matrix;
				}
				matrix[i][2] = third;
			}
			catch (exception e)
			{
				wasError = true;
				return matrix;
			}
		}
	}
	return matrix;
}

float** GetEmptyMatrix() 
{
	float** matrix = new float* [3];
	matrix[0] = new float[3];
	matrix[1] = new float[3];
	matrix[2] = new float[3];
	return matrix;
}

float CalcDeterminant(float** matrix)
{
	float determinant = 0;
	determinant += matrix[0][0] * matrix[1][1] * matrix[2][2];
	determinant += matrix[0][1] * matrix[1][2] * matrix[2][0];
	determinant += matrix[0][2] * matrix[1][0] * matrix[2][1];

	determinant -= matrix[0][2] * matrix[1][1] * matrix[2][0];
	determinant -= matrix[0][0] * matrix[1][2] * matrix[2][1];
	determinant -= matrix[0][1] * matrix[1][0] * matrix[2][2];
	return determinant;
}

float** Inverse(float** matrix, bool& wasError)
{
	float** inverseMatrix = GetEmptyMatrix();
	float determinant = CalcDeterminant(matrix);
	if (determinant == 0)
	{
		wasError = true;
		return matrix;
	}
	inverseMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	inverseMatrix[0][1] = matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2];
	inverseMatrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];

	inverseMatrix[1][0] = matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2];
	inverseMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
	inverseMatrix[1][2] = matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2];

	inverseMatrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
	inverseMatrix[2][1] = matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1];
	inverseMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			float number = inverseMatrix[i][j] / determinant;
			int floor = (int)floorf(number);
			float mod = number - floor;
			inverseMatrix[i][j] = floor + round(mod * 1000) / 1000;
		}
	}
	return inverseMatrix;
}
