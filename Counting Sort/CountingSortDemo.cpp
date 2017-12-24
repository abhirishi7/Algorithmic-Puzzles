/*
 * CountingSortDemo.cpp
 *
 *  Created on: 23-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include "CountingSortDemo.h"
#include<iostream>

using namespace std;

int* arrayC;
int* arrayB;
int* arrayA;

void sort(int n, int k) {

	////// initialize arrayC with all zero's.
	for (int i = 0; i <= k; i++)
		arrayC[i] = 0;

	///// fill up arrayC with the count of each integer from arayA.
	for (int i = 0; i < n; i++)
		arrayC[arrayA[i]] = arrayC[arrayA[i]] + 1;

	for (int i = 0; i <= k; i++) {
		cout << arrayC[i] << " ";
	}
	cout << endl;

	///// determine how many integers are behind a particular integer.
	for (int i = 1; i <= k; i++) {
		arrayC[i] = arrayC[i] + arrayC[i - 1];
	}

	for (int i = 0; i <= k; i++) {
		cout << arrayC[i] << " ";
	}
	cout << endl;

	for (int i = n - 1; i >= 0; i--) {
		arrayB[arrayC[arrayA[i]]] = arrayA[i];
		arrayC[arrayA[i]] = arrayC[arrayA[i]] - 1;
	}

	for (int i = 0; i < n; i++) {
		cout << arrayB[i] << " ";
	}
}

int main() {

	int n;
	int k = 0;

	cout << "Enter total elements : " << endl;
	cin >> n;
	arrayA = new int[n];
	cout << endl << "Enter elements : " << endl;
	for (int i = 0; i < n; i++) {
		cin >> arrayA[i];
		if (arrayA[i] > k)
			k = arrayA[i];
	}
	arrayC = new int[k + 1];
	arrayB = new int[n];
	sort(n, k);
	return 0;
}

