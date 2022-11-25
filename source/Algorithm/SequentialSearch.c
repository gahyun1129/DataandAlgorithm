#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode {
	int data;
	struct tagNode* nextNode;
} Node;

Node* SLL_SequentialSearch(Node* head, int target) {
	Node* current = head;
	Node* match = NULL;
	while (current != NULL) {
		if (current->data == target) {
			match == current;
			break;
		}
		else {
			current = current->nextNode;
		}
	}
	return match;
}

Node* SLL_moveToFront(Node** head, int target) {
	Node* current = (*head);
	Node* previous = NULL;
	Node* match = NULL;
	while (current != NULL) {
		if (current->data == target) {
			match == current;
			if (previous != NULL) {
				previous->nextNode = current->nextNode;
				current->nextNode = (*head);
				(*head) = current;
			}
			break;
		}
		else {
			previous = current;
			current = current->nextNode;
		}
	}
	return match;
}
Node* SLL_transpose(Node** head, int target) {
	Node* current = (*head);
	Node* pPrevious = NULL;
	Node* previous = NULL;
	Node* match = NULL;
	while (current != NULL) {
		if (current->data == target) {
			match == current;
			if (previous != NULL) {
				if (pPrevious != NULL) {
					pPrevious->nextNode = current;
				}
				else {
					(*head) = current;
				}
				previous->nextNode = current->nextNode;
				current->nextNode = (*head);
			}
			break;
		}
		else {
			if (previous != NULL) {
				pPrevious = previous;
			}
			previous = current;
			current = current->nextNode;
		}
	}
	return match;
}