/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include<iostream>
#include<vector>

using namespace std;

void squareAndSort(vector<int>& input) {
	if (input.size() == 0)
		return;

	int negEndIndex = 0;
	int posStartIndex = 0;
	vector<int> result;
	result.reserve(input.size());
	vector<int> negSquareResult;
	while (input.at(negEndIndex) < 0) {
		negSquareResult.push_back(
				input.at(negEndIndex) * input.at(negEndIndex));
		negEndIndex++;
	}
	posStartIndex = negEndIndex;
	negEndIndex--;
	// merge the two
	while (negEndIndex >= 0 && posStartIndex < input.size()) {
		int posSquare = input.at(posStartIndex) * input.at(posStartIndex);
		if (negSquareResult.at(negEndIndex) < posSquare) {
			result.push_back(negSquareResult.at(negEndIndex));
			negEndIndex--;
		} else {
			result.push_back(posSquare);
			posStartIndex++;
		}
	}
	while (negEndIndex >= 0) {
		result.push_back(negSquareResult.at(negEndIndex));
		negEndIndex--;
	}
	while (posStartIndex < input.size()) {
		int posSquare = input.at(posStartIndex) * input.at(posStartIndex);
		result.push_back(posSquare);
		posStartIndex++;
	}

	for(auto item : result){
		cout << item << " ";
	}
}

int main() {

	vector<int> input;
	size_t n;
	cin >> n;
	int num;
	for (size_t i = 0; i < n; i++) {
		cin >> num;
		input.push_back(num);
	}
	squareAndSort(input);
	return 0;
}
