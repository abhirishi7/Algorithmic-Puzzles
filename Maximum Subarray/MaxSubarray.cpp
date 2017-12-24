/*
 * MaxSubarray.cpp
 *
 *  Created on: 03-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "MaxSubarray.h"
#include<iostream>
#include<vector>

using namespace std;

#define INT_MAX 9999;
#define INT_MIN -9999;
//vector<int> maxCrossSum(int *arr, int left, int mid, int right) {
//
//	int i = mid, j = mid+1;
//	int leftSumMax = -9999;
//	int leftSum = 0;
//	int leftLow = 0;
//	while (i >= left) {
//		leftSum += arr[i];
//		if (leftSum > leftSumMax) {
//			leftSumMax = leftSum;
//			leftLow = i;
//		}
//		i--;
//	}
//	int rightSumMax = -9999;
//	int rightSum = 0;
//	int rightHigh  = 0;
//	while (j <= right) {
//		rightSum += arr[j];
//		if (rightSum > rightSumMax) {
//			rightSumMax = rightSum;
//			rightHigh = j;
//		}
//		j++;
//	}
//
//	vector<int> crossSumMax(3);
//	crossSumMax[0] = leftLow;
//	crossSumMax[1] = rightHigh;
//	crossSumMax[2] = leftSumMax + rightSumMax;
//	return crossSumMax;
//}
//
//vector<int> maxSubArray(int *arr, int left, int right) {
//
//	if (left == right) {
//		vector<int> maxArray;
//		maxArray.push_back(left);
//		maxArray.push_back(right);
//		maxArray.push_back(arr[left]);
//		return maxArray;
//	}
//
//	int mid = (left + right) / 2;
//	vector<int> leftSum = maxSubArray(arr, left, mid);
//	vector<int> rightSum = maxSubArray(arr, mid + 1, right);
//	vector<int> crossSum = maxCrossSum(arr, left, mid, right);
//	if ((leftSum[2] > rightSum[2]) && (leftSum[2] > crossSum[2]))
//		return leftSum;
//	else if ((rightSum[2] > leftSum[2]) && (rightSum[2] > crossSum[2]))
//		return rightSum;
//	return crossSum;
//
//}

int* maxSubArray(int* array, int n) {

	int *maxSub = new int[3];
	int leftLow = 0;
	int rightHigh = 0;
	int maxSum = array[0];
	int currSum = array[0];
	int currValue = array[0];
	for (int i = 1; i < n; i++) {
		currSum += array[i];
		currValue = array[i];
		if (currValue > currSum) {
			currSum = currValue;
			leftLow = i;
			rightHigh = i;
		}
		if (currSum > maxSum) {
			maxSum = currSum;
			rightHigh = i;
		}
	}

	maxSub[0] = leftLow;
	maxSub[1] = rightHigh;
	maxSub[2] = maxSum;
	return maxSub;

}

int main() {

	int n;
	cout << "Enter array size : ";
	cin >> n;

	cout << "Enter array elements : ";
	int *arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
//	vector<int> maxArray = maxSubArray(arr, 0, n - 1);
//	vector<int> :: iterator itr;
//	for (itr = maxArray.begin(); itr != maxArray.end(); ++itr)
//		cout << *itr << " ";

	int *maxSubArr = maxSubArray(arr, n);
	cout << maxSubArr[0] << " " << maxSubArr[1] << " " << maxSubArr[2];

	return 0;
}

