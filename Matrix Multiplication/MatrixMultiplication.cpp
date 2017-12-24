/*
 * MatrixMultiplication.cpp
 *
 *  Created on: 03-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "MatrixMultiplication.h"
#include<iostream>

using namespace std;

int** matrixMul(int r1, int c1, int r2, int c2, int** mat1, int** mat2) {

	int** result = new int*[r1];

	for (int i = 0; i < r1; i++) {
		result[i] = new int[c2];
		for (int j = 0; j < c2; j++) {
			result[i][j] = 0;
			for (int k = 0; k < c1; k++) {
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return result;
}

int main() {

	int r1, c1, r2, c2;
	cin >> r1 >> c1 >> r2 >> c2;
	cout << "Enter matrix 1" << endl;
	int **mat1 = new int*[r1];
	for (int i = 0; i < r1; i++) {
		mat1[i] = new int[c1];
		for (int j = 0; j < c1; j++)
			cin >> mat1[i][j];
	}
	cout << "Enter matrix 2" << endl;
	int **mat2 = new int*[r2];
	for (int i = 0; i < r2; i++) {
		mat2[i] = new int[c2];
		for (int j = 0; j < c2; j++)
			cin >> mat2[i][j];
	}
	int** mul = matrixMul(r1, c1, r2, c2, mat1, mat2);
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			cout << mul[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

