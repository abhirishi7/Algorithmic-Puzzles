/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include <iostream>
#include<math.h>

using namespace std;

void print(int** arr, int n, int m, int k) {
	cout << endl;
	for (int i = 0 + k; i < n + k; i++) {
		for (int j = 0 + k; j < m + k; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void calc(int ** arr, int n, int m) {

	int min = (n > m) ? m : n;
	int limit = ceil(min / 2);
	int val = 10;
	int row, col = 0;
	int k = 0;
	while (k <= limit) {
		row = n - (2 * k);
		col = m - (2 * k);

		// for top
		for (int i = 0 + k; i < col + k; i++) {
			arr[k][i] = val++;
		}

		// for right
		for (int i = 1 + k; i < row + k; i++) {
			arr[i][col + k - 1] = val++;
		}

		// for bottom
		for (int i = col + k - 2; i >= 0 + k; i--) {
			arr[row + k - 1][i] = val++;
		}

		// for left
		for (int i = row + k - 2; i > 0 + k; i--) {
			arr[i][k] = val++;
		}
		k++;
	}
	print(arr, n,m,0);
}

int main() {

	int n = 8;
	int m = 7;
	int val = 10;
	int **arr = new int*[n];
	for (int i = 0; i < n; i++) {
		int *row = new int[m];
		for (int j = 0; j < m; j++) {
			row[j] = val++;
		}
		arr[i] = &row[0];
	}

	print(arr, n, m, 0);
	calc(arr, n, m);

	return 0;
}
