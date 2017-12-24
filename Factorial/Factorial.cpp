/*
 * Factorial.cpp
 *
 *  Created on: 22-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include "Factorial.h"
#include<iostream>
using namespace std;

int fact(int n){
	if(n ==1)
		return 1;

	return n*fact(n-1);

}

int main(){

int n;
cout << "Enter n";
cin >> n;
cout << fact(n);
	return 0;
}
