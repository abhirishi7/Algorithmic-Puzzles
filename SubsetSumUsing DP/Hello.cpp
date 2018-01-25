/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include <iostream>

using namespace std;

int **dp;

bool isSubsetSum(int* input, int n, int sum) {

	if (n == 0 && sum != 0)
		return false;

	if (sum == 0)
		return true;
	if (sum < 1)
		return false;

	if (dp[n][sum] != -1) {
		if (dp[n][sum] == 0)
			return false;
		return true;
	}

	bool result = false;
	result = isSubsetSum(input, n - 1, sum)
			|| isSubsetSum(input, n - 1, sum - input[n - 1]);

	if (result == false)
		dp[n][sum] = 0;
	else
		dp[n][sum] = 1;
	return result;
}

int main() {
	int n = 6;
	int *arr = new int[n] { 1, 34, 3, 12, 1, 3 };
	int sum = 9;

	dp = new int*[n + 1];
	for (int i = 0; i <= n; i++) {
		int *row = new int[sum + 1];
		for (int j = 0; j <= sum; j++) {
			row[j] = -1;
		}
		dp[i] = &row[0];
	}

	if (isSubsetSum(arr, n, sum)) {
		cout << "There is a subset" << endl;
	} else {
		cout << "There is no subset" << endl;
	}

	delete arr;
	return 0;
}
