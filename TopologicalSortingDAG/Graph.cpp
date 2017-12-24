/*
 * Graph.cpp
 *
 *  Created on: 06-Nov-2017
 *      Author: Abhishek Tripathi
 */

#include<iostream>
#include<list>
#include<stack>

using namespace std;

class Graph {
private:
	int totalVertices;
	list<int> *adjList;
	stack<int> cycleStack;
	int cycleInt;
	bool topologicalSortUtil(int, bool*, stack<int>&,bool*);
public:
	Graph(int v) {
		totalVertices = v;
		adjList = new list<int>[totalVertices]();
	}
	void addEdge(int, int);
	void topologicalSort();
};

void Graph::topologicalSort() {

	stack<int> Stack;
	bool *recStack  = new bool[totalVertices];

	bool *visited = new bool[totalVertices];
	for (int i = 0; i < totalVertices; i++){
		visited[i] = false;
		recStack[i] = false;
	}

	for (int i = 0; i < totalVertices; i++) {
		if (visited[i] == false)
			if(topologicalSortUtil(i, &visited[0], Stack, recStack)){
				cout << "Cycle is : ";
				while(true){
					cout << cycleStack.top() << " ";
					if(cycleStack.top() == cycleInt)
						return;
					cycleStack.pop();
				}
			}
	}

	cout << "Topological sort is : " ;
	while (!Stack.empty()) {
		cout << Stack.top() << " ";
		Stack.pop();
	}
}

bool Graph::topologicalSortUtil(int source, bool *visited, stack<int> &Stack, bool *recStack) {

	visited[source] = true;
	recStack[source] = true;
	cycleStack.push(source);

	list<int>::iterator iter;
	for (iter = adjList[source].begin(); iter != adjList[source].end();
			iter++) {
		if (visited[*iter] == false){
			if(topologicalSortUtil(*iter, visited, Stack,recStack))
				return true;
		}
		else if(recStack[*iter]){
			cycleInt = *iter;
			return true;
		}
	}

	recStack[source] = false;
	Stack.push(source);
	cycleStack.pop();
	return false;
}

void Graph::addEdge(int source, int dest) {
	adjList[source].push_back(dest);
}

int main() {
	Graph g(8);
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(0,5);
	g.addEdge(1,4);
	g.addEdge(2,3);
	g.addEdge(3,0);
	g.addEdge(4,3);
	g.addEdge(4,5);
	g.addEdge(4,6);
	g.addEdge(4,7);
	g.addEdge(5,6);
	g.addEdge(7,6);
	g.topologicalSort();
	return 0;
}

