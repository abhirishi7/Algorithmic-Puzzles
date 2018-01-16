/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */
#include <iostream>
#include <unordered_set>
#include<vector>
#include<algorithm>

using namespace std;

string mergeStrings(string a, string b) {

int aLen = a.length(); // length of first string
	if (aLen == 0)
		return b; // return second string if first string is empty
	int bLen = b.length(); // length of second string
	if (b.length() == 0)
		return a; // return first string if second string is empty.

	int i = 0;
	int j = 0;
	string mergedString("");
	bool isFirst = true; // a bool to switch between 2 strings.
	while (i < aLen && j < bLen) {
		if (isFirst) {
			mergedString += a[i];
			i++;
			isFirst = false;
		} else {
			mergedString += b[j];
			j++;
			isFirst = true;
		}
	}

	while (i < aLen) { // make sure to append remaining characters from string 1, if any.
		mergedString += a[i];
		i++;
	}
	while (j < bLen) { // make sure to append remaining characters from string 2, if any.
		mergedString += b[j];
		j++;
	}
	return mergedString;
}

int main() {

	string a = "ab";
	string b = "zsd";
	cout << mergeStrings(a,b);
	return 0;
}
