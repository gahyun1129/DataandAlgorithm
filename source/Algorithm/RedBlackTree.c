#include <stdio.h>
#include <stdlib.h>

extern RBTNode* Nil;

typedef struct tagRBTreeNode {
	struct tagRBTreeNode* parent;
	struct tagRBTreeNode* right;
	struct tagRBTreeNode* left;

	enum {RED, BLACK} color;

	int data;
} RBTNode;

void RBT_rotateRight(RBTNode** root, RBTNode* parent) {
	//leftChild = 부모의 왼쪽 자식 노드
	RBTNode* leftChild = parent->left;
	//부모의 왼쪽 자식 노드 = 부모의 왼쪽 자식 노드의 오른쪽 자식 노드
	parent->left = leftChild->right;

	//왼쪽 자식 노드의 오른쪽 자식 노드가 있다면 그 노드의 부모 노드는 본인의 부모 노드로 연결. (자식->부모 관계 단절)
	if (leftChild->right != Nil) {
		leftChild->right->parent = parent;
	}
	//왼쪽 자식 노드의 부모 노드 = 부모의 부모 노드
	leftChild->parent = parent->parent;

	//부모의 부모 노드가 없다면 root.
	if (parent->parent == NULL) { (*root) = leftChild; }
	else { //부모가 부모 노드의 어느쪽 자식인지 확인 후 연결.
		if (parent == parent->parent->left) { parent->parent->left = leftChild; }
		else { parent->parent->right = leftChild; }
	}
	
	//왼쪽 자식 노드의 오른쪽 자식 노드를 부모 노드로 설정.
	leftChild->right = parent;
	//부모의 부모 노드를 왼쪽 자식 노드로 설정.
	parent->parent = leftChild;
}

void RBT_rotateLeft(RBTNode** root, RBTNode* parent) {
	RBTNode* rightChild = parent->right;
	parent->right = rightChild->left;

	if (rightChild->left != Nil) {
		rightChild->left->parent = parent;
	}
	rightChild->parent = parent->parent;

	if (parent->parent == NULL) { (*root) = rightChild; } //parent == root인 경우
	else {
		if (parent == parent->parent->left) { parent->parent->left = rightChild; }
		else { parent->parent->right = rightChild; }
	}

	rightChild->left = parent;
	parent->parent = rightChild;
}

void RBT_rebuildAfterInsert(RBTNode** root, RBTNode* X) {
	//X가 root이거나 부모의 색이 검은색이면 규칙 위반이 아니므로 반복 종료
	while (X != (*root) && X->parent->color == RED) {
		//X의 부모가 할아버지의 왼쪽 자식이면 삼촌 노드는 오른쪽 자식.
		if (X->parent == X->parent->parent->left) {
			RBTNode* Uncle = X->parent->parent->right;
			if (Uncle->color == RED) {
				X->parent->color = BLACK;
				Uncle->color = BLACK;
				X->parent->parent->color = RED;

				X = X->parent->parent;
			}
			else {
				//삼촌이 검은색이고 x가 오른쪽 자식인 경우
				if (X == X->parent->right) {
					//부모 노드를 새로 삽입한 노드라 하고 부모 노드를 기준으로 좌회전.
					X = X->parent;
					RBT_rotateLeft(root, X);
				}
				//본래 새로 삽입한 노드 (이하 부모 노드)를 검정, 할아버지 노드의 색을 빨간색으로 칠함.
				X->parent->color = BLACK;
				X->parent->parent->color = RED;
				//할아버지 노드를 기준으로 우회전하며 3번의 경우 마무리.
				RBT_rotateRight(root, X->parent->parent);
			}
		}
		else if (X->parent == X->parent->parent->right) {
			RBTNode* Uncle = X->parent->parent->left;
			if (Uncle->color == RED) {
				X->parent->color = BLACK;
				Uncle->color = BLACK;
				X->parent->parent->color = RED;

				X = X->parent->parent;
			}
			else {
				//삼촌이 검은색이고 x가 오른쪽 자식인 경우
				if (X == X->parent->left) {
					//부모 노드를 새로 삽입한 노드라 하고 부모 노드를 기준으로 좌회전.
					X = X->parent;
					RBT_rotateRight(root, X);
				}
				//본래 새로 삽입한 노드 (이하 부모 노드)를 검정, 할아버지 노드의 색을 빨간색으로 칠함.
				X->parent->color = BLACK;
				X->parent->parent->color = RED;
				//할아버지 노드를 기준으로 우회전하며 3번의 경우 마무리.
				RBT_rotateLeft(root, X->parent->parent);
			}
		}
	}
	(*root)->color = BLACK;
}

RBTNode* RBT_RemoveNode(RBTNode** root, int data) {
	RBTNode* removed = NULL;
	RBTNode* successor = NULL;
	RBTNode* target = RBT_searchNode((*root), data);

	if (target == NULL) {
		return NULL;
	}
	if (target->left == Nil || target->right == Nil) {
		removed = target;
	}
	else {
		removed = RBT_searchMinNode(target->right);
		target->data = removed->data;
	}

	if (removed->left != Nil) {
		successor = removed->left;
	}
	else {
		successor = removed->right;
	}

	successor->parent = removed->parent;

	if (removed->parent == NULL) {
		(*root) = successor;
	}
	else {
		if (removed == removed->parent->left) { removed->parent->left = successor; }
		else { removed->parent->right = successor; }
	}
	if (removed->color == BLACK) {
		RBT_rebuildAfterRemove(root, successor);
	}

	return removed;
}

void RBT_rebuildAfterRemove(RBTNode** root, RBTNode* successor) {
	RBTNode* sibling = NULL;

	while (successor->parent != NULL && successor->color == BLACK) {
		if (successor == successor->parent->left) {
			sibling = successor->parent->right;
			if (sibling->color == RED) {
				sibling->color = BLACK;
				successor->parent->color = RED;
				RBT_rotateLeft(root, successor->parent);
			}
			else {
				if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
					sibling->color = RED;
					successor = successor->parent;
				}
				else {
					if (sibling->left->color == RED) {
						sibling->left->color = BLACK;
						sibling->color = RED;

						RBT_rotateRight(root, sibling);
						sibling = successor->parent->right;
					}
					sibling->color = successor->parent->color;
					successor->parent->color = BLACK;
					sibling->right->color = BLACK;
					RBT_rotateLeft(root, successor->parent);
					successor = (*root);
				}
			}
		}
		else {
			//이중 흑색 노드가 부모 노드의 오른쪽 자식인 경우
		}
	}
	successor->color = BLACK;
}