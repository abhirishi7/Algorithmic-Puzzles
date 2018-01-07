/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include<utility>

using namespace std;


string findFirstRepeatingChar(string s) {

	if(s.length() == 0)
		return "";


	unordered_map<char,int> charCountMap;
	unordered_map<char,int> charFirstOccurMap;
	int len = s.length();
	int i = 0;
	while( i < len){
		if(charCountMap.find(s[i]) == charCountMap.end()){ // if not present
			charCountMap.insert(std::make_pair<char,int>((char)s[i],1));
			charFirstOccurMap.insert(std::make_pair<char,int>((char)s[i],(int)i));
		}else{
			auto val = charCountMap.find(s[i]);
			val->second = val->second + 1;
		}
		i++;
	}

	if(charCountMap.size() == 0)
		return "";

	string firstChar ="";
	int firstIndex = INT32_MAX;
	for(auto entry : charCountMap){
		if(entry.second > 1){
			auto iter = charFirstOccurMap.find(entry.first);
			if(iter->second < firstIndex){
				firstIndex = iter->second;
				firstChar = iter->first;
			}
		}
	}
	return firstChar;
}

int main() {
	string a = "abcba";
	cout << findFirstRepeatingChar(a);
	return 0;
}
