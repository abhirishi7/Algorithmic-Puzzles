/*
 * RodCut.cpp
 *
 *  Created on: 29-Nov-2017
 *      Author: Abhishek Tripathi
 */

#include<iostream>
#define NEG_INF INT32_MIN

using namespace std;

int *r;

template<typename T>
auto rodCutDP(T* price, int n) {

	auto maxPrice = 0;
	if (r[n] != NEG_INF)
		return r[n];
	if (n == 0)
		maxPrice = 0;
	else {
		maxPrice = NEG_INF;
		for (auto i = 1; i < n; i++) {
			maxPrice = max(maxPrice,
					rodCutDP(price, i) + rodCutDP(price, n - i));
		}
		maxPrice = max(maxPrice,price[n-1]);
	}

	r[n] = maxPrice;
	return r[n];
}

template<typename T>
auto rodCut(T* price, int n){
	return rodCutDP<T>(price, n);
}

int main() {

	int price[] { 3, 5, 8, 9, 10, 17, 17, 20 };
	int n = sizeof(price) / sizeof(int);
	r = new int[n+1];
	for (auto i = 0; i <= n; i++) {
		r[i] = NEG_INF;
	}
	cout << rodCut<int>(&price[0], n);
	return 0;
}

