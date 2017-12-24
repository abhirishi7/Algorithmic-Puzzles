/*
 * QuickSort.cpp
 *
 *  Created on: 30-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include "QuickSort.h"
#include<iostream>

using namespace std;

void swap(int *a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int medianSelection(int *arr, int left, int right) {
	int mid = (left + right) / 2;
	if (arr[mid] < arr[left])
		swap(&arr[left], &arr[mid]);
	if (arr[right] < arr[left])
		swap(&arr[right], &arr[left]);
	if (arr[right] < arr[mid])
		swap(&arr[right], &arr[mid]);

	swap(&arr[mid], &arr[right - 1]);
	return arr[right - 1];
}

void quickSort(int *arr, int left, int right) {
	if ((left + 1) >= right) {
		if (arr[left] > arr[right])
			swap(arr[left], arr[right]);
		return;
	}

	int pivot = medianSelection(arr, left, right);
	int i = left;
	int j = right - 1;
	for (;;) {
		while (arr[++i] < pivot) {
		}
		while (arr[--j] > pivot) {
		}
		if (i < j)
			swap(&arr[i], &arr[j]);
		else
			break;
	}

	swap(&arr[i], &arr[right - 1]);
	quickSort(arr, left, i - 1);
	quickSort(arr, i + 1, right);

}

int main() {
	int n;
	cout << "Enter array size : ";
	cin >> n;
	int *arr = new int[n];
	cout << "Enter array elements : ";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	quickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	return 0;
}

