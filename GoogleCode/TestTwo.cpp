/*
 * TestTwo.cpp
 *
 *  Created on: 20-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "TestTwo.h"

#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<stack>

using namespace std;
bool** adjacencyMatrix;
int vrtxCount;

void createAdjMatrix(vector<int> A, int vertexCount, vector<int> E) {
	adjacencyMatrix = new bool*[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		adjacencyMatrix[i] = new bool[vertexCount];
		for (int j = 0; j < vertexCount; j++)
			adjacencyMatrix[i][j] = false;
	}
	for (unsigned int i = 0; i < E.size() - 2; i = i + 2) {
		adjacencyMatrix[E[i]][E[i + 1]] = true;
		adjacencyMatrix[E[i + 1]][E[i]] = true;
	}
}

set<int> createLabelSet(vector<int> A) {

	set<int> labelSet;
	for (unsigned int i = 0; i < A.size(); i++) {
		labelSet.insert(A[i]);
	}
	return labelSet;
}

map<int, vector<int>> getLabelVerticesList(vector<int> A, set<int> labels) {

	map<int, vector<int>> labelVerticesList;
	set<int>::iterator setItr;
	for (setItr = labels.begin(); setItr != labels.end(); ++setItr) {
		vector<int> verticesList;
		for (unsigned int i = 0; i < A.size(); i++) {
			if (A[i] == *setItr)
				verticesList.push_back(i);
		}
		labelVerticesList.insert(
				std::pair<int, vector<int>>(*setItr, verticesList));
	}

	return labelVerticesList;
}

bool isPath(int src, int dest, int N) {
	bool visited[N] = { false };
	visited[src] = true;
	std::stack<int> next;
	next.push(src);

	while (!next.empty()) {
		int cv = next.top();
		next.pop();

		for (int nv = 0; nv < N; ++nv) {
			if (!visited[nv] && adjacencyMatrix[cv][nv] == 1) {
				visited[nv] = true;
				next.push(nv);
			}
		}
	}

	return visited[dest];
}

int pathLength(vector<int> verticesList) {

	// just check if first is connected to all other nodes or not
	int firstNode = verticesList[0];
	for (unsigned int i = 1; i < verticesList.size(); i++) {
		if (!isPath(firstNode, verticesList[i], vrtxCount))
			return 0;
	}
	return verticesList.size();
}

int getPath(map<int, vector<int>>::iterator mapItr) {

	vector<int> verticesList = mapItr->second;
	return pathLength(verticesList);
}

int solution(vector<int> &A, vector<int> &E) {
	int vertexCount = A.size();
	vrtxCount = A.size();
	createAdjMatrix(A, vertexCount, E);
	// unique labels
	set<int> labels = createLabelSet(A);
	// collect vector of vertices for a particular label
	map<int, vector<int>> labelVerticesList = getLabelVerticesList(A, labels);
	int longestPath = 0;
	map<int, vector<int>>::iterator mapItr;
	for (mapItr = labelVerticesList.begin(); mapItr != labelVerticesList.end();
			++mapItr) {

		int path = getPath(mapItr);
		if (path > longestPath)
			longestPath = path;
	}

	return longestPath;
}

int main() {

	return 0;

}

