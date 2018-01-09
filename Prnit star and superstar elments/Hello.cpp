/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef struct Result {
	stack<int> star;
	int superStar;
	Result(const stack<int>& star, int super) :
			star(star), superStar(super) {
	}
} Result;

const Result getStarElements(const vector<int>& input) {

	stack<int> starElements;
	int superStar;
	int i = 0;
	int max = -9999;
	int maxIndexfromRight = -1;
	int maxindexfromLeft = -1;
	while (i < input.size()) {
		if (input.at(i) > max) {
			max = input.at(i);
			maxindexfromLeft = i;
		}
		i++;
	}
	max = -9999;
	i = input.size() - 1;
	while (i >= 0) {
		if (input.at(i) > max) {
			max = input.at(i);
			starElements.push(max);
			maxIndexfromRight = i;
		}
		i--;
	}
	if (maxindexfromLeft == maxIndexfromRight) {
		superStar = input[maxindexfromLeft];
	} else {
		superStar = -1;
	}
	Result result(starElements, superStar);
	return result;
}

int main() {

	int totalCases;
	cin >> totalCases;
	vector<int> input;
	vector<Result> result;
	int num;
	int arraySize;
	for (auto i = 0; i < totalCases; i++) {
		cin >> arraySize;
		input.clear();
		input.reserve(arraySize);
		for (auto j = 0; j < arraySize; j++) {
			cin >> num;
			input.push_back(num);
		}
		result.push_back(getStarElements(input));
	}
	for (auto val : result) {
		while(!val.star.empty()) {
			cout << val.star.top() << " ";
			val.star.pop();
		}
		cout << endl << val.superStar << endl;
	}
	return 0;
}
