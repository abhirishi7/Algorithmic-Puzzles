/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;

const int MAX_CHAR = 26;

string compare(const vector<int>& list1, const vector<int>& list2) {
	vector<int>::const_iterator iter1 = list1.begin();
	vector<int>::const_iterator iter2 = list2.begin();
	for (; iter1 != list1.end(), iter2 != list2.end(); iter1++, iter2++) {
		if (*iter1 != *iter2) {
			return "NO";
		}
	}
	return "YES";
}

int getSign(char val) {
	return (val == '+') ? 1 : -1;
}

void parse(string& input, vector<int>& list) {
	stack<char> signs;
	size_t i = 0;
	while (i < input.length()) {
		if (i == 0 && input[i] != '(' && input[i] != '-' && input[i] != '+') {
			list[input[i] - 'a'] += 1;
			i++;
			continue;
		}
		if (input[i] == '(') {
			if (i == 0) {
				signs.push('+');
			} else {
				if (signs.empty())
					signs.push(input[i - 1]);
				else if (signs.top() == '-') {
					if (input[i - 1] == '-')
						signs.push('+');
					else
						signs.push('-');
				} else {
					if (input[i - 1] == '-')
						signs.push('-');
					else
						signs.push('+');
				}
			}
			i++;
		} else if (input[i] == ')') {
			signs.pop();
			i++;
		} else if (input[i] == '-' || input[i] == '+') {
			i++;
		} else {
			if (input[i - 1] == '(') {
				//if (signs.empty()) {
				//	literalsMap.insert(make_pair(input[i], input[i - 1]));
				//} else {
				list[input[i] - 'a'] += getSign(signs.top());
				//}
			} else {
				if (signs.empty()) {
					list[input[i] - 'a'] += getSign(input[i - 1]);
				} else {
					if (signs.top() == '-') {
						if (input[i - 1] == '-') {
							list[input[i] - 'a'] += 1;
						} else {
							list[input[i] - 'a'] += -1;
						}
					} else {
						if (input[i - 1] == '-') {
							list[input[i] - 'a'] += -1;
						} else {
							list[input[i] - 'a'] += 1;
						}
					}
				}
			}
			i++;
		}
	}
}

string evaluate(string& first, string& second) {
	vector<int> list1(MAX_CHAR, 0);
	vector<int> list2(MAX_CHAR, 0);
	parse(first, list1);
	parse(second, list2);
	return compare(list1, list2);
}

int main() {

	int n;
	cin >> n;
	vector<string> result;
	result.reserve(n);
	string first { "" };
	string second { "" };
	for (auto i = 0; i < n; i++) {
		cin >> first >> second;
		result.push_back(evaluate(first, second));
	}
	for (auto ans : result) {
		cout << ans << endl;
	}
	return 0;
}
