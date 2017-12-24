/*
 * InsertionSort.cpp
 *
 *  Created on: 24-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include<iostream>

using namespace std;


void sort(const int& input[], size_t n){
	auto i=1;
	int key;
	auto j = 0;
	while(i < n){
		key = input[i];
		j = i-1;
		while(j >=0 && input[j] > key){
			input[j+1] = input[j];
			j--;
		}
		input[j+1] = key;
		i++;
	}
}

int main() {
	size_t n;
	cin >>n;
	int input[n];
	for(size_t i=0;i<n;i++)
		cin >> input[i];
	sort(input,n);
	return 0;
}

