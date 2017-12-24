/*
 * ProblemOne.cpp
 *
 *  Created on: 26-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "ProblemOne.h"
#include<iostream>
#include<vector>
#include<stack>

using namespace std;

string isBalanced(string value) {
	typedef struct charArray {
		char braces[2];
	} charArray;
	stack<char> currStack;
	vector<charArray> validBraces;
	char currentBrace;
	charArray charArr = { '{', '}' };
	validBraces.push_back(charArr);
	charArr = {'(',')'};
	validBraces.push_back(charArr);
	charArr = {'[',']'};
	validBraces.push_back(charArr);

	for (unsigned int i = 0; i < value.length(); i++) {
		currentBrace = value[i];
		for (int j = 0; j < 3; j++) {
			if (validBraces[j].braces[1] == currentBrace) {
				if (currStack.empty())
					return "NO";
				char top = currStack.top();
				currStack.pop();
				if (top != validBraces[j].braces[0])
					return "NO";
			} else if (validBraces[j].braces[0] == currentBrace)
				currStack.push(currentBrace);
		}
	}
	if (currStack.empty())
		return "YES";
	return "NO";
}

vector<string> braces(vector<string> values) {

	vector<string> result;
	for (unsigned int i = 0; i < values.size(); i++) {
		result.push_back(isBalanced(values[i]));
	}
	return result;
}

int main() {
	vector<string> values;
	int n = 2;
	//cin >> n;
	//for (int i = 0; i < n; i++)
	//cin >> values[i];
	values.push_back("{}()[]");
	values.push_back("{[}]}");
	braces(values);
	return 0;
}

