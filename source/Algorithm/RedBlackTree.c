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
	//leftChild = �θ��� ���� �ڽ� ���
	RBTNode* leftChild = parent->left;
	//�θ��� ���� �ڽ� ��� = �θ��� ���� �ڽ� ����� ������ �ڽ� ���
	parent->left = leftChild->right;

	//���� �ڽ� ����� ������ �ڽ� ��尡 �ִٸ� �� ����� �θ� ���� ������ �θ� ���� ����. (�ڽ�->�θ� ���� ����)
	if (leftChild->right != Nil) {
		leftChild->right->parent = parent;
	}
	//���� �ڽ� ����� �θ� ��� = �θ��� �θ� ���
	leftChild->parent = parent->parent;

	//�θ��� �θ� ��尡 ���ٸ� root.
	if (parent->parent == NULL) { (*root) = leftChild; }
	else { //�θ� �θ� ����� ����� �ڽ����� Ȯ�� �� ����.
		if (parent == parent->parent->left) { parent->parent->left = leftChild; }
		else { parent->parent->right = leftChild; }
	}
	
	//���� �ڽ� ����� ������ �ڽ� ��带 �θ� ���� ����.
	leftChild->right = parent;
	//�θ��� �θ� ��带 ���� �ڽ� ���� ����.
	parent->parent = leftChild;
}

void RBT_rotateLeft(RBTNode** root, RBTNode* parent) {
	RBTNode* rightChild = parent->right;
	parent->right = rightChild->left;

	if (rightChild->left != Nil) {
		rightChild->left->parent = parent;
	}
	rightChild->parent = parent->parent;

	if (parent->parent == NULL) { (*root) = rightChild; } //parent == root�� ���
	else {
		if (parent == parent->parent->left) { parent->parent->left = rightChild; }
		else { parent->parent->right = rightChild; }
	}

	rightChild->left = parent;
	parent->parent = rightChild;
}

void RBT_rebuildAfterInsert(RBTNode** root, RBTNode* X) {
	//X�� root�̰ų� �θ��� ���� �������̸� ��Ģ ������ �ƴϹǷ� �ݺ� ����
	while (X != (*root) && X->parent->color == RED) {
		//X�� �θ� �Ҿƹ����� ���� �ڽ��̸� ���� ���� ������ �ڽ�.
		if (X->parent == X->parent->parent->left) {
			RBTNode* Uncle = X->parent->parent->right;
			if (Uncle->color == RED) {
				X->parent->color = BLACK;
				Uncle->color = BLACK;
				X->parent->parent->color = RED;

				X = X->parent->parent;
			}
			else {
				//������ �������̰� x�� ������ �ڽ��� ���
				if (X == X->parent->right) {
					//�θ� ��带 ���� ������ ���� �ϰ� �θ� ��带 �������� ��ȸ��.
					X = X->parent;
					RBT_rotateLeft(root, X);
				}
				//���� ���� ������ ��� (���� �θ� ���)�� ����, �Ҿƹ��� ����� ���� ���������� ĥ��.
				X->parent->color = BLACK;
				X->parent->parent->color = RED;
				//�Ҿƹ��� ��带 �������� ��ȸ���ϸ� 3���� ��� ������.
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
				//������ �������̰� x�� ������ �ڽ��� ���
				if (X == X->parent->left) {
					//�θ� ��带 ���� ������ ���� �ϰ� �θ� ��带 �������� ��ȸ��.
					X = X->parent;
					RBT_rotateRight(root, X);
				}
				//���� ���� ������ ��� (���� �θ� ���)�� ����, �Ҿƹ��� ����� ���� ���������� ĥ��.
				X->parent->color = BLACK;
				X->parent->parent->color = RED;
				//�Ҿƹ��� ��带 �������� ��ȸ���ϸ� 3���� ��� ������.
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
			//���� ��� ��尡 �θ� ����� ������ �ڽ��� ���
		}
	}
	successor->color = BLACK;
}