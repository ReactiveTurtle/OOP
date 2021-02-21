#include <iostream>
using namespace std;

double CalcDeterminant(double** matrix, int matrixSize);

double** Transpose(double** matrix);

int main()
{
	double** matrix = new double* [3];
	matrix[0] = new double[3];
	matrix[0][0] = 20;
	matrix[0][1] = 10;
	matrix[0][2] = 12;

	matrix[1] = new double[3];
	matrix[1][0] = 3;
	matrix[1][1] = 0;
	matrix[1][2] = 5;

	matrix[2] = new double[3];
	matrix[2][0] = 9;
	matrix[2][1] = 15;
	matrix[2][2] = 20;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double buffer = matrix[i][j];
			cout << buffer << " ";
		}
		cout << endl;
	}
	cout << CalcDeterminant(matrix, 3) << endl;
	matrix = Transpose(matrix);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double buffer = matrix[i][j];
			cout << buffer << " ";
		}
		cout << endl;
	}
}

double** GetSubMatrix(int skipRow, int skipCol, double** matrix, int matrixSize) {
	int newMatrixSize = matrixSize - 1;
	double** newMatrix = new double* [newMatrixSize * 2];
	int rowCounter = 0;
	int colCounter = 0;
	for (int i = 0; i < matrixSize; i++) {
		if (i == skipRow) {
			continue;
		}
		double row[newMatrixSize] = { 0 };
		for (int j = 0; j < matrixSize; j++) {
			if (j == skipCol) {
				continue;
			}
			double value = matrix[i][j];
			row[colCounter] = value;
			colCounter++;
		}
		newMatrix[rowCounter] = row;
		rowCounter++;
	}
	for (int i = 0; i < newMatrixSize; i++) {
		for (int j = 0; j < newMatrixSize; j++) {
			double buffer = newMatrix[i][j];
			cout << buffer << " ";
		}
		cout << endl;
	}
	cout << "------------" << endl;
	return newMatrix;
}

double CalcDeterminant(double** matrix, int matrixSize) {
	double determinant = 0;
	if (matrixSize == 1) {
		return matrix[0][0];
	}
	int signFactor = 1;
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			determinant += signFactor *
				CalcDeterminant(GetSubMatrix(i, j, matrix, matrixSize), matrixSize - 1);
			signFactor *= -1;
		}
	}
	return determinant;
}

double** Transpose(double** matrix) {
	int matrixSize = sizeof(matrix);
	double** transposedMatrix = new double* [matrixSize];
	transposedMatrix[0] = new double[matrixSize];
	transposedMatrix[1] = new double[matrixSize];
	transposedMatrix[2] = new double[matrixSize];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			transposedMatrix[j][i] = matrix[i][j];
		}
	}
	return transposedMatrix;
}
