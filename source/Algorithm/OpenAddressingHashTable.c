#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* keyType;
typedef char* valueType;

enum elementStatus {
	empty = 0, occupied = 1
};

typedef struct tagElementType {
	keyType key;
	valueType value;

	enum elementStatus status;
} elementType;

typedef struct tagHashTable {
	int occupiedcount;
	int tableSize;

	elementType* table;
} hashTable;

hashTable* createHashTable(int tableSize) {
	hashTable* h = (hashTable*)malloc(sizeof(hashTable));
	h->table = (elementType*)malloc(sizeof(elementType) * tableSize);

	memset(h->table, 0, sizeof(elementType) * tableSize);

	h->tableSize = tableSize;
	h->occupiedcount = 0;

	return h;
}

void set(hashTable** h, keyType key, valueType value) {
	int keyLen, address, stepSize;
	double usage;

	//임계치 확인
	usage = (double)(*h)->occupiedcount / (*h)->tableSize;

	//임계치가 50% 이상인 경우 rehash
	if (usage > 0.5) { rehash(h); }

	//최초 해시값 및 고정폭 연산
	keyLen = strlen(key);
	address = hash(key, keyLen, (*h)->tableSize);
	stepSize = hash2(key, keyLen, (*h)->tableSize);

	//충돌의 경우 연산
	while ((*h)->table[address].status != empty && strcmp((*h)->table[address].key, key) != 0) {
		address = (address + stepSize) % (*h)->tableSize;
	}

	//삽입하기
	(*h)->table[address].key = (char*)malloc(sizeof(char) * (keyLen + 1));
	strcpy((*h)->table[address].key, key);
	(*h)->table[address].value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
	strcpy((*h)->table[address].value, value);

	(*h)->table[address].status = occupied;

	(*h)->occupiedcount++;
}

valueType get(hashTable* h, keyType key) {
	int keyLen = strlen(key);

	int address = hash(key, keyLen, h->tableSize);
	int stepSize = hash2(key, keyLen, h->tableSize);

	while (h->table[address].status != empty && strcmp(h->table[address].key, key) != 0) {
		address = (address + stepSize) % h->tableSize;
	}

	return h->table[address].value;
}

void clearElement(elementType* element) {
	if (element->status == empty) { return; }

	free(element->key);
	free(element->value);
}

void destroyHashTable(hashTable* h) {
	int i = 0;
	for (i = 0; i < h->tableSize; i++) {
		clearElement(&(h->table[i]));
	}

	free(h->table);
	free(h);
}
int hash(keyType key, int keyLength, int tableSize) {
	int i = 0, hashValue = 0;
	for (i = 0; i < keyLength; i++) {
		hashValue = (hashValue << 3) + key[i];
	}
	hashValue = hashValue % tableSize;
	return hashValue;
}

int hash2(keyType key, int keyLength, int tableSize) {
	int i = 0, hashValue = 0;
	for (i = 0; i < keyLength; i++) {
		hashValue = (hashValue << 2) + key[i];
	}
	hashValue = hashValue % (tableSize - 3);
	return hashValue + 1;
}

void rehash(hashTable** h) {
	int i = 0;
	elementType* oldTable = (*h)->table;

	hashTable* newH = createHashTable((*h)->tableSize * 2);
	for (i = 0; i < (*h)->tableSize; i++) {
		if (oldTable[i].status == occupied) {
			set(&newH, oldTable[i].key, oldTable[i].value);
		}
	}
	destroyHashTable((*h));
	(*h) = newH;
}
