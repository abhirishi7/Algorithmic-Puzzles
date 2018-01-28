/*
 * Hello.cpp
 *
 *  Created on: 20-Aug-2017
 *      Author: Abhishek Tripathi
 */

#include <unordered_set>
#include <vector>

using namespace std;

int solution(vector<vector<int> > &A) {
	// write your code in C++14 (g++ 6.2.0)

	unordered_set<long> colorSet;
	for (vector<int> rows : A) {
		for (auto val : rows) {
			colorSet.insert(val);
		}
	}
	int uniqueColCount = colorSet.size();
	int row = A.size();
	int col = A[0].size();
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i - 1 >= 0) {
				if (A[i][j] == A[i - 1][j])
					continue;
			}
			if (i + 1 < row) {
				if (A[i][j] == A[i + 1][j])
					continue;
			}
			if (j - 1 >= 0) {
				if (A[i][j] == A[i][j - 1])
					continue;
			}
			if (j + 1 < col) {
				if (A[i][j] == A[i][j + 1])
					continue;
			}
			count++;
		}
	}
	return count + uniqueColCount;
}

int main() {

	vector<vector<int>> A;
	A[0][0] = 5;
	A[0][1] = 4;
	A[0][2] = 4;
	A[1][0] = 4;
	A[1][1] = 3;
	A[1][2] = 4;
	A[2][0] = 3;
	A[2][1] = 2;
	A[2][2] = 4;
	A[3][0] = 2;
	A[3][1] = 2;
	A[3][2] = 2;
	A[4][0] = 3;
	A[4][1] = 3;
	A[4][2] = 4;
	A[5][0] = 1;
	A[5][1] = 4;
	A[5][2] = 4;
	A[6][0] = 4;
	A[6][1] = 1;
	A[6][2] = 1;
	solution(A);
	return 0;
}
