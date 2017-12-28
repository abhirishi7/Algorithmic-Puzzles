/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

string getEquiBinaryForm(int m) {
	string result;
	int rem = 0;
	while (m >= 1) {
		rem = m % 2;
		result.append(to_string(rem));
		m = m / 2;
	}
	reverse(result.begin(), result.end());
	return result;
}

char printNumber(int m, int k, int n) {
	string binaryStr = getEquiBinaryForm(m);
	for (auto i = 0; i < n; i++) {
		for (size_t j = 0; j < binaryStr.length(); j = j + 2) {
			if (binaryStr[j] == '0')
				binaryStr.replace(j, 1, "01");
			else
				binaryStr.replace(j, 1, "10");
		}
	}
	return binaryStr[k];
}

int main() {
	int tot;
	cin >> tot;
	vector<int> testCases;
	vector<char> result;
	testCases.reserve(tot);
	int m = 0, k = 0, n = 0;
	for (auto i = 0; i < tot; i++) {
		cin >> m >> k >> n;
		result.push_back(printNumber(m, k, n));
	}
	for (char ans : result)
		cout << ans << endl;

	return 0;
}
