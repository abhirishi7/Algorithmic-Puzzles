/*
 * MergeSort.cpp
 *
 *  Created on: 22-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include "MergeSort.h"
#include<iostream>
using namespace std;
int n;

void printArray(int* array, int length) {
	for (int i = 0; i < length; i++)
		cout << array[i] << " ";
}

void mergeHalves(int* array, int* temp, int leftStart, int leftEnd,
		int rightStart, int rightEnd) {

	int i = leftStart;
	int j = rightStart;
	int index = leftStart;
	while ((i <= leftEnd) && (j <= rightEnd)) {
		if (array[i] < array[j]) {
			temp[index] = array[i];
			i++;
		} else {
			temp[index] = array[j];
			j++;
		}
		index++;
	}
	while (i <= leftEnd) {
		temp[index] = array[i];
		index++;
		i++;
	}
	while (j <= rightEnd) {
		temp[index] = array[j];
		index++;
		j++;
	}
	for(int i = leftStart;i<=rightEnd;i++){
		array[i] = temp[i];
	}
}

void mergeSort(int *array, int* temp, int leftStart, int rightEnd) {

	if (leftStart >= rightEnd)
		return;
	int mid = (leftStart + rightEnd) / 2;
	mergeSort(array, temp, leftStart, mid);
	mergeSort(array, temp, mid + 1, rightEnd);
	mergeHalves(array, temp, leftStart, mid, mid + 1, rightEnd);
}

int main() {
	cout << "Enter array size";
	cin >> n;
	int *array = new int[n];
	int* temp = new int[n];
	for (int i = 0; i < n; i++)
		cin >> array[i];
	//printArray(array,n);
	//int array2[8] = {2,4,1,6,8,5,3,7};

	mergeSort(array, temp, 0, n - 1);
	printArray(temp, n);
	return 0;
}
