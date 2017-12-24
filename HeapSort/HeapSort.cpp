/*
 * HeapSort.cpp
 *
 *  Created on: 16-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "HeapSort.h"
#include<iostream>

using namespace std;

int n;
int heapSize;

void swap(int *a, int *b) {

	int temp = *a;
	*a = *b;
	*b = temp;
}

void maxHeapify(int *arr, int index) {

	int i = index;
	int largest = 0;
	int largestIndex = 0;
	while (i <= heapSize / 2) {
		largest =
				(arr[2 * i] > arr[(2 * i) + 1]) ? arr[2 * i] : arr[(2 * i) + 1];
		largestIndex =
				(arr[2 * i] > arr[(2 * i) + 1]) ? (2 * i) : ((2 * i) + 1);
		if (arr[i] >= largest)
			break;
		swap(arr[i], arr[largestIndex]);
		i = largestIndex;
	}
}

void buildMaxHeap(int *arr) {

	int i = n >> 1; /// (equivalent to n/2)divide by 2 with better efficiency
	while (i >= 0) {
		maxHeapify(arr, i);
		i--;
	}
}

void heapSort(int *arr) {

	buildMaxHeap(arr);
	int i = n - 1;
	while (i > 0) {
		// exchange A[1] with A[i]
		swap(&arr[0], &arr[i]);
		heapSize -= 1;
		i--;
		maxHeapify(arr, 0);
	}
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
}

int main() {

	cout << "Enter n";
	cin >> n;
	heapSize = n;
	int *arr = new int[n];
	cout << " Enter array elements";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	heapSort(arr);
	return 0;
}

