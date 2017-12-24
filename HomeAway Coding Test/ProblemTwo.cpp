/*
 * ProblemTwo.cpp
 *
 *  Created on: 26-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "ProblemTwo.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;

vector<string> parseLines(vector<string> fileLines) {

	vector<string> result;
	map<string, int> outputMap;
	for (unsigned int i = 0; i < fileLines.size(); i++) {
		int firstIndex = fileLines[i].find('[');
		string parsedInput = fileLines[i].substr(firstIndex + 1, 20);
		if (outputMap.find(parsedInput) != outputMap.end()) {
			std::map<string, int>::iterator it = outputMap.find(parsedInput);
			it->second = it->second + 1;
		} else {
			outputMap.insert(std::make_pair(parsedInput, 1));
		}
	}
	std::map<string, int>::iterator it;
	for (it = outputMap.begin(); it != outputMap.end(); ++it) {
		if (it->second > 0)
			result.push_back(it->first);
	}
	return result;
}

//int main() {
//	string fileName;
//	string outFileName;
//	cin >> fileName;
//	outFileName = "req_" + fileName;
//	ofstream fout(outFileName);
//	ifstream inFile(fileName);
//	string line;
//	vector<string> fileLines;
//	while (getline(inFile, line)) {
//		fileLines.push_back(line);
//	}
//	vector<string> result = parseLines(fileLines);
//	for (unsigned int i = 0; i < result.size(); i++)
//		fout << result[i] << endl;
//	return 0;
//}

