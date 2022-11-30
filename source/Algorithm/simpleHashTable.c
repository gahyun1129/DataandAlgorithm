#include <stdio.h>
#include <stdlib.h>

typedef int keyType;
typedef int valueType;

typedef struct tagNode {
	keyType key;
	valueType value;
} Node;

typedef struct tagHashTable {
	int tableSize;
	Node* table;
} hashTable;

hashTable* createHashTable(int tableSize) {
	hashTable* HT = (hashTable*)malloc(sizeof(hashTable));
	HT->table = (Node*)malloc(sizeof(Node) * tableSize);
	HT->tableSize = tableSize;

	return HT;
}

void set(hashTable* h, keyType key, valueType value) {
	int address = hash(key, h->tableSize);
	h->table[address].key = key;
	h->table[address].value = value;
}

valueType get(hashTable* h, keyType key) {
	int address = hash(key, h->tableSize);
	return h->table[address].value;
}

void destroyHashTable(hashTable* h) {
	free(h->table);
	free(h);
}
int hash(int input, int tableSize) { return input % tableSize; }

int hash_DigitsFolding(char* key, int keyLength, int tableSize) {
	int i = 0, hashValue = 0;
	for (i = 0; i < keyLength; i++) {
		hashValue = (hashValue << 3) + key[i];
	}

	return hashValue % tableSize;
}