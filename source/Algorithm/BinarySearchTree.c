#include <stdio.h>
#include <stdlib.h>

typedef struct tagBSTNode {
	int data;
	struct tagBSTNode* left;
	struct tagBSTNode* right;
} BSTNode;

BSTNode* BST_SearchNode(BSTNode* tree, int target) {
	if (tree = NULL) { return NULL; }
	if (tree->data == target) { return tree; }
	else if (tree->data > target) { return BST_SearchNode(tree->left, target); }
	else { return BST_SearchNode(tree->right, target); }
}

void BST_insetNode(BSTNode* tree, BSTNode* child) {
	if (tree->data < child->data) {
		if (tree->right == NULL) { tree->right = child; }
		else { BST_insetNode(tree->right, child); }
	}
	else if (tree->data > child->data) {
		if (tree->left == NULL) { tree->left = child; }
		else { BST_insetNode(tree->left, child); }
	}
}

BSTNode* BST_removeNode(BSTNode* tree, BSTNode* parent, int target) {
	BSTNode* removed = NULL;
	if (tree == NULL) { return NULL; }
	if (tree->data > target) { removed = BST_removeNode(tree->left, tree, target); }
	else if (tree->data < target) { removed = BST_removeNode(tree->right, tree, target); }
	else {
		removed = tree;
		if (tree->left == NULL && tree->right == NULL) {
			if (parent->left == tree) { parent->left = NULL; }
			else { parent->right = NULL; }
		}
		else if (tree->left == NULL || tree->right == NULL) {
			BSTNode* temp;
			if (tree->left != NULL) { temp = tree->left; }
			else { temp = tree->right; }

			if (parent->left != NULL) { parent->left = temp; }
			else { parent->right = temp; }
		}
		else {
			BSTNode* min = BST_SearchMinNode(tree->right);
			min = BST_removeNode(tree, NULL, min->data);
			tree->data = min->data;
		}
	}
	return removed;
}
BSTNode* BST_SearchMinNode(BSTNode* tree) {
	if (tree == NULL) {
		return NULL;
	}
	if (tree->left == NULL) {
		return tree;
	}
	else {
		return BST_SearchMinNode(tree->left);
	}
}