/*
 * BigSorting.cpp
 *
 *  Created on: 29-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include "BigSorting.h"
#include<iostream>

using namespace std;

void mergeHalves(int * values, int* temp, int n, int leftStart, int leftEnd,
		int rightStart, int rightEnd) {

	int i = leftStart;
	int j = rightStart;
	int index = 0;
	while (i <= leftEnd && j <= rightEnd) {
		if (values[i] < values[j]) {
			temp[index] = values[i];
			i++;
		} else {
			temp[index] = values[j];
			j++;
		}
		index++;
	}
	while (i <= leftEnd) {
		temp[index] = values[i];
		i++;
		index++;
	}
	while (j <= rightEnd) {
		temp[index] = values[j];
		j++;
		index++;
	}

	for (int i = 0; i < n; i++)
		values[i] = temp[i];
}

void insertionSort(int* values, int n) {
	int key;
	for (int i = 1; i < n; i++) {
		key = values[i];
		int j = i -1;
		while (j >= 0 && (values[j] > key)) {
			values[j+1] = values[j];
			j--;
		}
		values[j+1] = key;
	}
}

void mergeSort(int * values, int * temp, int n, int leftStart, int rightEnd) {

	if (n < 30) //////for lower values of n perform insertion sort for optimization
		return insertionSort(values, n);

	int mid = (leftStart + rightEnd) / 2;
	mergeSort(values, temp, n, leftStart, mid);
	mergeSort(values, temp, n, mid + 1, rightEnd);
	mergeHalves(values, temp, n, leftStart, mid, mid + 1, rightEnd);

}

void bigSort(int *values, int* temp, int n) {
	mergeSort(values, temp, n, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << values[i] << endl;
}

int main() {
	int n;
	cin >> n;
	int *values = new int[n];
	int* temp = new int[n];
	string value = "";
	for (int i = 0; i < n; i++) {
		cin >> value;
		values[i] = stoi(value);
	}
	bigSort(values, temp, n);
	return 0;
}

