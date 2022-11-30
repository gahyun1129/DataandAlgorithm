#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* keyType;
typedef char* valueType;

typedef struct tagNode {
	keyType key;
	valueType value;

	struct tagNode* next;
} Node;

typedef Node* list;

typedef struct tagHashTable {
	int tableSize;
	list* table;
} hashTable;

int hash_DigitsFolding(char* key, int keyLength, int tableSize) {
	int i = 0, hashValue = 0;
	for (i = 0; i < keyLength; i++) {
		hashValue = (hashValue << 3) + key[i];
	}

	return hashValue % tableSize;
}
valueType get(hashTable* h, keyType key) {
	int address = hash_DigitsFolding(key, strlen(key), h->tableSize);

	list theList = h->table[address];
	list target = NULL;

	if (theList == NULL) {
		return NULL;
	}

	while (1) {
		if (strcmp(theList->key, key) == 0) {
			target = theList;
			break;
		}
		if (theList->next == NULL) {
			break;
		}
		else {
			theList = theList->next;
		}
	}
	return target->value;
}

void set(hashTable* h, keyType key, valueType value) {
	int address = hash_DigitsFolding(key, strlen(key), h->tableSize);
	Node* newNode = createNode(key, value);

	if (h->table[address] == NULL) {
		h->table[address] = newNode;
	}
	else {
		list L = h->table[address];
		newNode->next = L;
		h->table[address] = newNode;

		printf("Collision occured : Key(%s), Adrress(%d)\n", key, address);
	}
}