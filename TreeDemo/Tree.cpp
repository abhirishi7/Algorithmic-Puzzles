/*
 * Tree.cpp
 *
 *  Created on: 03-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "Tree.h"
#include<iostream>

using namespace std;

typedef struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
} BstNode;

class BinarySearchTree {
private:
	BstNode* getNewNode(int);
public:
	BstNode* insert(BstNode*, int);
	BstNode* search(BstNode*, int);
	int minElement(BstNode*);
	int maxElement(BstNode*);
	int findHeight(BstNode*);
};

BstNode* BinarySearchTree::getNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

BstNode* BinarySearchTree::insert(BstNode* root, int data) {
	if (root == NULL) {
		root = getNewNode(data);
	} else if (data < root->data) {
		root->left = insert(root->left, data);
	} else {
		root->right = insert(root->right, data);
	}

	return root;
}

BstNode* BinarySearchTree::search(BstNode* root, int data) {

	if (root == NULL)
		return NULL;
	if (root->data == data)
		return root;

	if (data < root->data)
		return search(root->left, data);
	else
		return search(root->right, data);
}

int BinarySearchTree::minElement(BstNode* root) {

	if (root->left == NULL)
		return root->data;

	return minElement(root->left);
}

int BinarySearchTree::maxElement(BstNode* root) {
	if (root->right == NULL)
		return root->data;

	return maxElement(root->right);
}

int BinarySearchTree::findHeight(BstNode* root) {
	if (root == NULL)
		return -1;

	return max(findHeight(root->left), findHeight(root->right)) + 1;
}

int main() {
	BinarySearchTree bst;
	BstNode* root = NULL;
	root = bst.insert(root, 15);
	root = bst.insert(root, 10);
	root = bst.insert(root, 20);
	root = bst.insert(root, 25);
	root = bst.insert(root, 8);
	root = bst.insert(root, 12);

	return 0;
}

