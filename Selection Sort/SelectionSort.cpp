/*
 * SelectionSort.cpp
 *
 *  Created on: 27-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include "SelectionSort.h"
#include<iostream>

using namespace std;

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Sort(int n, int *arr) {

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[i]) {
				swap(&arr[j], &arr[i]);
			}
		}
	}
for(int i=0;i<n;i++)
	cout << arr[i] << " ";
}

int main() {

	int n;
	cout << "Enter total elements : ";
	cin >> n;
	cout << "Enter elements :";
	int *array = new int[n];
	for (int i = 0; i < n; i++)
		cin >> array[i];
	Sort(n, array);
	return 0;
}

