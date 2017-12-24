/*
 * QueenMinConflict.cpp
 *
 *  Created on: 21-Oct-2017
 *      Author: Abhishek Tripathi
 */

#include "QueenMinConflict.h"
#include<iostream>

using namespace std;

typedef struct stateNode {
	int** state;
	int heuristicCost;
	stateNode** neighbours;  //// to be removed later.
	stateNode* bestNeighbour;
	int totalNeighbours;
	int* queenIndexes;
} stateNode;

class MinConflict {

private:
	int boardSize;
	stateNode* currentState;
	stateNode* auxCurrentState;

public:
	MinConflict(int n) {
		boardSize = n;
	}
	void setInitialState();   ////// done
	void printSolution(stateNode*);  ///// done
	int getHeuristicCost(stateNode*);  ///// done
	void generateNeighbours(stateNode*);
	stateNode* generateBestNeighbour(stateNode*);
	void startMinConflictSearch(); //// done
	void randomRestart();
	stateNode* randomQueenPlacement();  ////// done
};

void MinConflict::randomRestart() {
	currentState = randomQueenPlacement();
	currentState->heuristicCost = getHeuristicCost(currentState);
	startMinConflictSearch();
}

void MinConflict::printSolution(stateNode* solution) {
	if (solution == NULL) {
		cout << "No solution found !!!";
		return;
	}
	cout << endl;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			cout << solution->state[i][j] << " ";
		}
		cout << endl;
	}
}

void MinConflict::startMinConflictSearch() {
	while (true) {
		if (currentState->heuristicCost == 0) {
			printSolution(currentState);
			break;
		} else {
			currentState->bestNeighbour = generateBestNeighbour(currentState);
			if (currentState->bestNeighbour != NULL)
				currentState = currentState->bestNeighbour;
			else {
				randomRestart();
				return;
			}
		}
	}
}

stateNode* MinConflict::generateBestNeighbour(stateNode* node) {

	int currHeuristic = node->heuristicCost;
	stateNode* bestNeighbour = NULL;
	int minConflictIndex;
	for (int col = 0; col < boardSize; col++) {
		int queenIndex = node->queenIndexes[col];
		minConflictIndex = queenIndex;
		for (int i = 0; i < boardSize; i++) {
			if (i == queenIndex)
				continue;

			stateNode* neighbour = new stateNode();
			int** tempState = new int*[boardSize];
			int* tempQueenIndexes = new int[boardSize];
			for (int k = 0; k < boardSize; k++) {
				int* temp = new int[boardSize];
				memcpy(temp, node->state[k], boardSize * sizeof(int));
				tempState[k] = &temp[0];
			}
			memcpy(tempQueenIndexes, node->queenIndexes,boardSize * sizeof(int));

			tempState[i][col] = 1;
			tempState[queenIndex][col] = 0;
			tempQueenIndexes[col] = i;
			neighbour->state = tempState;
			neighbour->queenIndexes = tempQueenIndexes;
			neighbour->heuristicCost = getHeuristicCost(neighbour);
			if (neighbour->heuristicCost < currHeuristic) {
				bestNeighbour = neighbour;
				currHeuristic = neighbour->heuristicCost;
				minConflictIndex = i;
			}
		}
		int prev = node->queenIndexes[col];
		node->state[prev][col] = 0;
		node->state[minConflictIndex][col] = 1;
		node->queenIndexes[col] = minConflictIndex;
	}
	return bestNeighbour;
}

int MinConflict::getHeuristicCost(stateNode* node) {
	int cost = 0;
	for (int k = 0; k < boardSize - 1; k++) {
		int i = node->queenIndexes[k];
		int j = k;
		while (i > 0 && j < (boardSize - 1)) { // diagonal up
			i--;
			j++;
			if (node->state[i][j] == 1)
				cost++;
		}
		i = node->queenIndexes[k];
		j = k;
		while (i < (boardSize - 1) && j < (boardSize - 1)) { // diagonal down
			i++;
			j++;
			if (node->state[i][j] == 1)
				cost++;
		}
		i = node->queenIndexes[k];
		j = k;
		while (j < (boardSize - 1)) {
			j++;
			if (node->state[i][j] == 1)
				cost++;
		}

	}
	return cost;
}

void MinConflict::setInitialState() {
	currentState = randomQueenPlacement();
	currentState->heuristicCost = getHeuristicCost(currentState);
}

stateNode* MinConflict::randomQueenPlacement() {
	stateNode* node = new stateNode();
	int* queenIndexes = new int[boardSize];
	int** state = new int*[boardSize];
	for (int i = 0; i < boardSize; i++) {
		int* row = new int[boardSize];
		int randomIndex = rand() % boardSize;
		queenIndexes[i] = randomIndex;
		for (int j = 0; j < boardSize; j++) {
			row[j] = 0;
		}
		state[i] = &row[0];
	}
	for (int i = 0; i < boardSize; i++) {
		state[queenIndexes[i]][i] = 1;
	}
	node->state = state;
	node->queenIndexes = queenIndexes;
	return node;
}

int main() {

	int boardSize;
	cout << "Enter total number of queens." << endl;
	//cin >> boardSize;
	MinConflict minConflict(50);
	minConflict.setInitialState();
	minConflict.startMinConflictSearch();
	return 0;
}

