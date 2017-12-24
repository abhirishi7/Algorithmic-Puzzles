/*
 * EightPuzzle.cpp
 *
 *  Created on: 23-Sep-2017
 *      Author: Abhishek Tripathi
 * Student Id : 801010002
 *
 */

#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<time.h>
#include<math.h>
#include<algorithm>

using namespace std;

typedef struct stateNode {  // structure definition of a state node
	stateNode* link1; // link to first child, corresponding to up movement.
	stateNode* link2; // link to second child, corresponding to down movement.
	stateNode* link3; // link to third child, corresponding to right movement.
	stateNode* link4; // link to fourth child, corresponding to left movement.
	stateNode* parent; // link to parent state node.
	int** state; // matrix representation of node's state.
	int distance; // distance from the root.i.e level cost
	int cost; // heuristic cost value for this node.
	bool isDirty;
} stateNode;

/*
 * This structure is used as a comparator for priority queue.
 */
struct comp {
	bool operator()(const stateNode* a, const stateNode* b) {
		return a->cost > b->cost;
	}
};

/*
 * Search tree class contains information about the structure of state node,
 * queue of active nodes to be expanded,
 * list of already expanded nodes,
 * count of generated and expanded nodes,
 * initial state matrix representation,
 * goal state matrix representation,
 * member functions to operate on these properties.
 */
class SearchTree {

private:

	stateNode* root; // root node of search tree.
	int rowSize;
	int colSize;
	int blankValue;
	priority_queue<stateNode*, vector<stateNode*>, comp> activeNodes;
	vector<stateNode*> activeNodesAux;
	vector<stateNode*> visitedNodes; // list of all visited or expanded nodes.
	int** initialState; // matrix representation of initial state of 8 puzzle problem.
	int** goalState; // matrix representation of goal state of 8 puzzle problem.
	int totalNodesGenerated; // count of total no. of nodes generated so far.
	int totalNodesExpanded; // count of total no. of nodes expanded/visited so far.

public:
	SearchTree() {
		rowSize = 3;
		colSize = 3;
		blankValue = 0;
		totalNodesExpanded = 0;
		totalNodesGenerated = 0;
	}
	;

	void generateRoot();
	void displayNode(stateNode*);
	void printSolutionPath(stateNode*);
	void setInitialAndFinalState();
	void findSolution();
	bool checkIfGoalState(stateNode*);
	int getHeuristicCost(stateNode*);
	bool isQueueEmpty(priority_queue<stateNode*, vector<stateNode*>, comp>);
	vector<int*> getValidMoves(stateNode*);
	void generateNextStates(stateNode*);
	int** getNodeState(stateNode*, int*);
	void selectNextBestStates(vector<stateNode*>);
	bool isNodeAlreadyGenerated(stateNode*);
	void memoryCleanUp();
};

/*
 * Function displays the state array representation of the node passed as argument.
 */
void SearchTree::displayNode(stateNode* node) {
	cout << endl;
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			cout << node->state[i][j] << " ";
		}
		cout << endl;
	}
}

/*
 * Function takes goal state node as an argument and prints the search tree from root to goal state node.
 */
void SearchTree::printSolutionPath(stateNode* solutionNode) {
	int distance = solutionNode->distance;
	stack<stateNode*> solutionStack;
	while (solutionNode != NULL) { // add all the nodes from goal state to root node in stack.
		solutionStack.push(solutionNode);
		solutionNode = solutionNode->parent;
	}
	int levelCount = 0;
	while (!solutionStack.empty()) { // pop the top element from stack until stack gets empty.
		stateNode* node = solutionStack.top(); // this prints all the nodes from root to goal state.
		solutionStack.pop();
		if (levelCount) {
			cout << "  |" << endl;
			cout << "  |" << " f(n) = h(n) + g(n) = "
					<< (node->cost - node->distance) << " + " << node->distance
					<< endl;
			cout << "  |" << endl;
			cout << "  v";
		}
		displayNode(node);
		levelCount++;
	}
	cout << endl << "Total levels traversed : " << distance;
	cout << endl << "Total nodes generated : " << totalNodesGenerated;
	cout << endl << "Total nodes expanded : " << totalNodesExpanded;
}

/*
 * Function selects best state nodes for a particular parent node based on least heuristic cost.
 */
void SearchTree::selectNextBestStates(vector<stateNode*> nodes) {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		activeNodes.push(nodes[i]); // add it to the queue of active nodes, to be expanded later.
		activeNodesAux.push_back(nodes[i]);
	}
}

/*
 * For the node passed as argument, the functions returns list of valid movements allowed to generate next states.
 */
vector<int*> SearchTree::getValidMoves(stateNode* node) {
	vector<int*> validMoves;
	int blankPos[2];
	bool found = false;
	for (int i = 0; i < rowSize; i++) { // first, locate the position of blank tile in the state array.
		for (int j = 0; j < colSize; j++) {
			if (node->state[i][j] == blankValue) {
				found = true;
				blankPos[0] = i;
				blankPos[1] = j;
				break;
			}
		}
		if (found)
			break;
	}
	// check all possible cases of movement for validity;
	// 1. up
	if ((blankPos[0] - 1) >= 0) { // for up movement, limit is 0. It can't move upwards beyond zero.
		int* move = new int[2];
		move[0] = blankPos[0] - 1;
		move[1] = blankPos[1];
		validMoves.push_back(move);
	}
	// 2. down
	if ((blankPos[0] + 1) <= (rowSize - 1)) { // for down movement, limit is row size, i.e 3 in this case.
		int* move = new int[2];
		move[0] = blankPos[0] + 1;
		move[1] = blankPos[1];
		validMoves.push_back(move);
	}
	// 3. right
	if ((blankPos[1] + 1) <= (colSize - 1)) { // for right movement, limit is column size, i.e 3 in this case.
		int* move = new int[2];
		move[0] = blankPos[0];
		move[1] = blankPos[1] + 1;
		validMoves.push_back(move);
	}
	// 4. left
	if ((blankPos[1] - 1) >= 0) { // for left movement, limit is 0. It can't move left beyond zero.
		int* move = new int[2];
		move[0] = blankPos[0];
		move[1] = blankPos[1] - 1;
		validMoves.push_back(move);
	}
	return validMoves;

}

/*
 *  This function generates the state representation of the new state node with the given valid move.
 */
int** SearchTree::getNodeState(stateNode* parentNode, int* validMove) {

	int blankPos[2];
	int** newState = new int*[rowSize];
	for (int i = 0; i < rowSize; i++) {
		int* temp = new int[colSize];
		for (int j = 0; j < colSize; j++) {
			temp[j] = parentNode->state[i][j];
			if (parentNode->state[i][j] == blankValue) {
				blankPos[0] = i;
				blankPos[1] = j;
			}
		}
		newState[i] = &temp[0];
	}

	int toChange = newState[validMove[0]][validMove[1]];
	newState[blankPos[0]][blankPos[1]] = toChange;
	newState[validMove[0]][validMove[1]] = blankValue;

	return newState;
}

/*
 * Function generates next state nodes for the parent node passed as an argument.
 * The next state nodes are generated based on the successor function i.e
 * move up, move down, move left, move right.
 */
void SearchTree::generateNextStates(stateNode* parentNode) {
	vector<int*> validMoves = getValidMoves(parentNode); // get the list of valid movements possible for the given state.
	vector<stateNode*> nodes;
	int count = 0;
	for (unsigned int i = 0; i < validMoves.size(); i++) { // for each valid move, generate the state node and fill out all properties.
		stateNode* newNode = new stateNode();
		newNode->distance = parentNode->distance + 1;
		newNode->link1 = NULL;
		newNode->link2 = NULL;
		newNode->link3 = NULL;
		newNode->link4 = NULL;
		newNode->parent = parentNode;
		newNode->state = getNodeState(parentNode, validMoves[i]);
		newNode->isDirty = false;
		newNode->cost = getHeuristicCost(newNode) + newNode->distance; // assign the heuristic cost to this new state node.
		if ((newNode->cost - parentNode->cost) < -1) { // bad move
			delete newNode;
			continue;
		}
		if (isNodeAlreadyGenerated(newNode)) // check if the new state node has already been generated before.
			delete newNode; // if yes, delete the node and continue with next valid node.
		else { // else, assign the link of parent node to this new state node.
			count++;
			switch (count) {
			case 1:
				parentNode->link1 = newNode;
				break;
			case 2:
				parentNode->link2 = newNode;
				break;
			case 3:
				parentNode->link3 = newNode;
				break;
			case 4:
				parentNode->link4 = newNode;
				break;
			}
			totalNodesGenerated += 1; // increment the total generated nodes count.
			nodes.push_back(newNode);
		}
	}
	selectNextBestStates(nodes); // out of the generated new state nodes, select the ones with least heuristic cost and distance.
}

/*
 * Function returns heuristic cost, h(n) for the node passed as an argument.
 * h(n) here is manhattan distance, i.e the numbers of horizontal and vertical moves it takes
 * to place a tile in its correct position.
 */
int SearchTree::getHeuristicCost(stateNode* node) {
	int cost = 0;
	bool found;
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			int currI = i;
			int currJ = j;
			found = false;
			for (int m = 0; m < rowSize; m++) {
				for (int n = 0; n < colSize; n++) {
					if (node->state[i][j] == goalState[m][n]
							&& (node->state[i][j] != blankValue)) {
						int finalI = m;
						int finalJ = n;
						cost += abs(finalI - currI) + abs(finalJ - currJ);
						found = true;
						break;
					}
					if (found)
						break;
				}
			}
		}
	}
	return cost;
}

/*
 * Function returns true if the node passed as an argument matches the state of goal state.
 * Else, it returns false.
 */
bool SearchTree::checkIfGoalState(stateNode* node) {
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++)
			if (node->state[i][j] != goalState[i][j]) // return false, if any of the state numbers do not match.
				return false;
	}
	return true;
}

/*
 *  Function returns boolean true if the node passed as an argument has already been generated previously.
 *  Else, returns boolean false.
 */
bool SearchTree::isNodeAlreadyGenerated(stateNode* node) {

	int count = 0;
	for (unsigned int i = 0; i < visitedNodes.size(); i++) { // for each node in the activeNodes queue, check if any of those
		for (int j = 0; j < (rowSize); j++) { // matches with the current node that is passed as an argument.
			for (int k = 0; k < colSize; k++)
				if (node->state[j][k] == visitedNodes[i]->state[j][k])
					count++;
		}
		if (count == (rowSize * colSize)) { // if count == (rowSize * colSize), means that all the numbers in the state matches with the particular node
			return true;
		}
		count = 0;
	}

	count = 0;
	for (unsigned int i = 0; i < activeNodesAux.size(); i++) { // for each node in the activeNodes queue, check if any of those
		for (int j = 0; j < (rowSize); j++) { // matches with the current node that is passed as an argument.
			for (int k = 0; k < colSize; k++)
				if (node->state[j][k] == activeNodesAux[i]->state[j][k])
					count++;
		}
		if (count == (rowSize * colSize)) { // if count == (rowSize * colSize), means that all the numbers in the state matches with the particular node
			if (activeNodesAux[i]->cost > node->cost) { // from the active nodes queue.
				activeNodesAux[i]->isDirty = true;
				activeNodesAux[i] = node;
				totalNodesGenerated--;
				return false;
			}
			return true;
		}
		count = 0;
	}

	return false;
}

/*
 * Calling function to A* algorithm.
 */
void SearchTree::findSolution() {

	if (root != NULL) { // check if root node represents the goal state, only if root != NULL.
		if (checkIfGoalState(root)) {
			printSolutionPath(root); // if root node is goal state, print solution and return to main.
			return;
		}
	}

	if (isQueueEmpty(activeNodes)) { // initially if queue of active nodes is empty, insert root node in the queue of active nodes.
		activeNodes.push(root);
		activeNodesAux.push_back(root);
		totalNodesGenerated += 1;  // increment the nodes generated count.
	}

	while (!isQueueEmpty(activeNodes)) { // loop while queue of active nodes is not empty.
		stateNode* currNode = activeNodes.top(); // pop the first element from queue.
		activeNodes.pop();
		if (currNode->isDirty)
			continue;
		if (checkIfGoalState(currNode)) { // check if the current node is goal state or not.
			printSolutionPath(currNode); // print the solution if current node = goal state and return to main.
			return;
		}
		visitedNodes.push_back(currNode); // push the current node to the list of visited/expanded nodes.
		totalNodesExpanded += 1; // increment the nodes visited count.
		generateNextStates(currNode); // generate next state nodes for the current node.
	}
}

/*
 *  This method return a boolean true is the current queue of active nodes to be expanded becomes empty.
 *  Else it returns boolean false.
 */
bool SearchTree::isQueueEmpty(
		priority_queue<stateNode*, vector<stateNode*>, comp> queue) {
	return !queue.size();
}

/*
 * Method to generate the root node of the search tree based on the initial state array.
 */
void SearchTree::generateRoot() {
	root = new stateNode();
	root->link1 = NULL;
	root->link2 = NULL;
	root->link3 = NULL;
	root->link4 = NULL;
	root->parent = NULL;
	root->distance = 0; // root is at level 0, so the distance is 0.
	root->state = new int*[rowSize];
	root->isDirty = false;
	for (int i = 0; i < rowSize; i++) {
		root->state[i] = new int[colSize];
		for (int j = 0; j < colSize; j++)
			root->state[i][j] = initialState[i][j]; // fill out the state of root based on the initial state array.
	}
	root->cost = getHeuristicCost(root); // assign h(n) or heuristic cost for root node.
}

/*
 *  This function takes user inputs for initial and goal state representation in a 2-d array.
 *  A blank position is represented by '0'.
 *
 */
void SearchTree::setInitialAndFinalState() {
	cout
			<< "Enter values for initial state (row - wise) with blank represented by '0'"
			<< endl;
	cout << "Example : " << " 1 2 3" << endl;
	cout << "           4 5 0" << endl;
	cout << "           6 7 8" << endl;
	initialState = new int*[rowSize];
	for (int i = 0; i < rowSize; i++) {
		int* temp = new int[colSize];
		for (int j = 0; j < colSize; j++) {
			cin >> temp[j];
		}
		initialState[i] = &temp[0];
	}
	cout << endl
			<< "Enter values for goal state (row - wise) with blank represented by '0'"
			<< endl;
	goalState = new int*[rowSize];
	for (int i = 0; i < rowSize; i++) {
		int* temp = new int[colSize];
		for (int j = 0; j < colSize; j++) {
			cin >> temp[j];
		}
		goalState[i] = &temp[0];
	}
}

/*
 *  Call to clean up heap memory and release all dynamically created objects so as to avoid any memory leak.
 */
void SearchTree::memoryCleanUp() {
	for (int i = 0; i < rowSize; i++) {
		delete initialState[i]; // delete all row pointers of initial state array.
		delete goalState[i];  // delete all row pointers of goal state array.
	}
	for (unsigned int i = 0; i < activeNodesAux.size(); i++) {
		int** state = activeNodesAux[i]->state;
		if (state == NULL)
			continue;
		//for (int j = 0; j < rowSize; j++)
		//delete state[j];
		//delete state;
		activeNodesAux[i]->parent = NULL;
		activeNodesAux[i]->link1 = NULL;
		activeNodesAux[i]->link2 = NULL;
		activeNodesAux[i]->link3 = NULL;
		activeNodesAux[i]->link4 = NULL;
	}
	delete initialState;
	delete goalState;
	delete root;
}

/*
 *  Driver function
 */
int main() {
	SearchTree searchTree;
	searchTree.setInitialAndFinalState(); // Set the initial and goal state for the 8 puzzle problem
	cout <<endl<< "Search tree creation started.... "<<endl;
	clock_t start = clock();
	searchTree.generateRoot(); // generate root node based on the initial state representation for the search tree.
	searchTree.findSolution();  // call to function that runs A* algorithm.
	clock_t finish = clock();
	cout << endl << endl << "Total running time : "
			<< (float(finish - start) / CLOCKS_PER_SEC) << " secs";
	searchTree.memoryCleanUp(); // call to clear all dynamic memory objects and release all resources.
	string exit;
	cin >> exit;
	return 0;
}

