#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Matrix3x3
{
	float items[3][3];
};

void PrintMatrix(Matrix3x3 matrix);
Matrix3x3 ParseMatrixInput(istream& input, bool& wasError);
Matrix3x3 Inverse(Matrix3x3 matrix, bool& wasError);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Not found name of input file" << endl;
		return 1;
	}
	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Input file not found" << endl;
		return 1;
	}
	bool wasError;

	Matrix3x3 matrix = ParseMatrixInput(input, wasError);
	if (wasError)
	{
		cout << "Invalid matrix in input file" << endl;
		return 1;
	}

	Matrix3x3 inverseMatrix = Inverse(matrix, wasError);
	if (wasError)
	{
		cout << "Matrix is degenerate" << endl;
		return 1;
	}
	PrintMatrix(inverseMatrix);
	return 0;
}

void PrintMatrix(Matrix3x3 matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << setprecision(matrix.items[i][j]) << (j == 2 ? "" : " ");
		}
		cout << endl;
	}
}

Matrix3x3 GetZeroMatrix()
{
	Matrix3x3 matrix;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix.items[i][j] = 0;
		}
	}
	return matrix;
}

Matrix3x3 ParseMatrixInput(istream& input, bool& wasError)
{
	wasError = false;
	Matrix3x3 matrix = GetZeroMatrix();
	string buffer;
	for (int i = 0; i < 3 && !wasError; i++)
	{
		if (!input.good()) {
			wasError = true;
			return matrix;
		}
		int j = 0;
		char ch;
		input >> ch;
		string numberBuffer = "";
		bool wasSpace = true;
		while (ch != '\n') {
			if (ch != ' ') {
				if (j == 3) {
					wasError = true;
					return matrix;
				}
				numberBuffer += ch;
			}
			else if (!wasSpace) {
				try
				{
					size_t errorPos;
					float number = stof(numberBuffer, &errorPos);
					numberBuffer = "";
					if (errorPos != numberBuffer.size()) {
						wasError = true;
						return matrix;
					}
					matrix.items[i][j] = number;
					wasSpace = true;
					j++;
				}
				catch (exception e)
				{
					wasError = true;
					return matrix;
				}
			}
			input >> ch;
		}
	}
	return matrix;
}

float CalcDeterminant(Matrix3x3 matrix)
{
	float determinant = 0;
	determinant += matrix.items[0][0] * matrix.items[1][1] * matrix.items[2][2];
	determinant += matrix.items[0][1] * matrix.items[1][2] * matrix.items[2][0];
	determinant += matrix.items[0][2] * matrix.items[1][0] * matrix.items[2][1];

	determinant -= matrix.items[0][2] * matrix.items[1][1] * matrix.items[2][0];
	determinant -= matrix.items[0][0] * matrix.items[1][2] * matrix.items[2][1];
	determinant -= matrix.items[0][1] * matrix.items[1][0] * matrix.items[2][2];
	return determinant;
}

Matrix3x3 Inverse(Matrix3x3 matrix, bool& wasError)
{
	wasError = false;
	Matrix3x3 inverseMatrix;
	float determinant = CalcDeterminant(matrix);
	if (determinant == 0)
	{
		wasError = true;
		return matrix;
	}
	inverseMatrix.items[0][0] = matrix.items[1][1] * matrix.items[2][2] - matrix.items[1][2] * matrix.items[2][1];
	inverseMatrix.items[0][1] = matrix.items[0][2] * matrix.items[2][1] - matrix.items[0][1] * matrix.items[2][2];
	inverseMatrix.items[0][2] = matrix.items[0][1] * matrix.items[1][2] - matrix.items[0][2] * matrix.items[1][1];

	inverseMatrix.items[1][0] = matrix.items[1][2] * matrix.items[2][0] - matrix.items[1][0] * matrix.items[2][2];
	inverseMatrix.items[1][1] = matrix.items[0][0] * matrix.items[2][2] - matrix.items[0][2] * matrix.items[2][0];
	inverseMatrix.items[1][2] = matrix.items[0][2] * matrix.items[1][0] - matrix.items[0][0] * matrix.items[1][2];

	inverseMatrix.items[2][0] = matrix.items[1][0] * matrix.items[2][1] - matrix.items[1][1] * matrix.items[2][0];
	inverseMatrix.items[2][1] = matrix.items[0][1] * matrix.items[2][0] - matrix.items[0][0] * matrix.items[2][1];
	inverseMatrix.items[2][2] = matrix.items[0][0] * matrix.items[1][1] - matrix.items[0][1] * matrix.items[1][0];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float number = inverseMatrix.items[i][j] / determinant;
		}
	}
	return inverseMatrix;
}
