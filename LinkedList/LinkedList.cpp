/*
 * LinkedList.cpp
 *
 *  Created on: 03-Sep-2017
 *      Author: Abhishek Tripathi
 */

#include "LinkedList.h"
#include<iostream>

using namespace std;

class Linkedlist {
public:
	int data;
	Linkedlist* next;
};

int main() {

	Linkedlist* head = NULL;
	Linkedlist* temp = new Linkedlist();
	temp->data = 2;
	temp->next = NULL;
	head = temp;
	Linkedlist* temp1 = new Linkedlist();
	temp->next = temp1;
	temp1->data = 4;
	temp1->next = NULL;
	Linkedlist* temp2 = new Linkedlist();
	temp1->next = temp2;
	temp2->data = 6;
	Linkedlist* temp3 = new Linkedlist();
	temp3->data = 1;
	temp2->next = temp3;
	temp3->next = NULL;

//	while (temp != NULL) {
//		cout << temp->data << " ";
//		temp = temp->next;
//	}

	///// reversing list
	Linkedlist* prev = head;
	Linkedlist* curr = prev->next;

	do{
		Linkedlist* nextNode = curr->next;
		if (prev == head)
			prev->next = NULL;
		curr->next = prev;
		prev = curr;
		curr = nextNode;
	}while(curr != NULL);
	head = prev;
	temp = head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
}

