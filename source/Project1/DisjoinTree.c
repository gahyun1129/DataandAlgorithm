#include <stdio.h>
#include <stdlib.h>

typedef struct tagDisjoinSet {
	struct tagDisjoinSet* parent;
	void* data;
} disjoinSet;

void DS_unionSet(disjoinSet* set1, disjoinSet* set2) {
	set2 = DS_findSet(set2);
	set2->parent = set1;
}

disjoinSet* DS_findSet(disjoinSet* Set) {
	while (Set->parent != NULL) {
		Set = Set->parent;
	}

	return Set;
}