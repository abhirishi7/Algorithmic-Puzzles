/*
 * Test.cpp
 *
 *  Created on: 10-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "Test.h"
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

int func(int *arr, int n, int k) {

	int count = 0;
	int pointer1;
	int pointer2;
	pointer1 = pointer2 = 0;
	for (int i = 1; i < n;) {
		if((arr[pointer1] + k) >= arr[i]){
			i++;
			continue;
		}

		pointer2 = i-1;
		while((arr[pointer2] + k) >= arr[i]){
			i++;
		}
		pointer1=pointer2=i;
		count++;
	}
	if(pointer1==pointer2)
		count++;

	return count;
}

int main() {

	int n, k;
	n=8;
	k=2;
	int arr[8] = {7,2,4,6,5,9,12,11};
	//cin >> n >> k;
	//int *arr = new int[n];
	//for (int i = 0; i < n; i++)
	//	cin >> arr[i];
	sort(arr,arr+n);
	cout << func(arr, n, k);
	return 0;
}
