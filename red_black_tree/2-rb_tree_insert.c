#include "rb_trees.h"

/**
 * bst_insert - Inserts a value into the tree as a BST
 *
 * @tree: Double pointer to the root of the tree
 * @value: Value to insert
 *
 * Return: Pointer to the newly inserted node, or NULL on failure
 */
rb_tree_t *bst_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *parent = NULL, *current = *tree;

	while (current)
	{
		parent = current;
		if (value < current->n)
			current = current->left;
		else if (value > current->n)
			current = current->right;
		else
			return (NULL); /* Value already exists */
	}

	return (rb_tree_node(parent, value, RED));
}

/**
 * rotate_left - Performs a left rotation on a node
 *
 * @tree: Double pointer to the root of the tree
 * @node: Node to rotate
 */
void rotate_left(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *right = node->right;

	if (!right)
		return;

	node->right = right->left;
	if (right->left)
		right->left->parent = node;

	right->parent = node->parent;
	if (!node->parent)
		*tree = right;
	else if (node == node->parent->left)
		node->parent->left = right;
	else
		node->parent->right = right;

	right->left = node;
	node->parent = right;
}

/**
 * rotate_right - Performs a right rotation on a node
 *
 * @tree: Double pointer to the root of the tree
 * @node: Node to rotate
 */
void rotate_right(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *left = node->left;

	if (!left)
		return;

	node->left = left->right;
	if (left->right)
		left->right->parent = node;

	left->parent = node->parent;
	if (!node->parent)
		*tree = left;
	else if (node == node->parent->left)
		node->parent->left = left;
	else
		node->parent->right = left;

	left->right = node;
	node->parent = left;
}

/**
 * fix_violation - Fixes Red-Black Tree violations after insertion
 *
 * @tree: Double pointer to the root of the tree
 * @node: Newly inserted node
 */
void fix_violation(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent, *grandparent, *uncle;

	while (node != *tree && node->parent && node->parent->color == RED)
	{
		parent = node->parent;
		grandparent = parent->parent;

		if (parent == grandparent->left)
		{
			uncle = grandparent->right;
			if (uncle && uncle->color == RED)
			{
				/* Case 1: Recolor */
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				node = grandparent;
			}
			else
			{
				if (node == parent->right)
				{
					/* Case 2: Left-Right */
					rotate_left(tree, parent);
					node = parent;
					parent = node->parent;
				}
				/* Case 3: Left-Left */
				rotate_right(tree, grandparent);
				parent->color = BLACK;
				grandparent->color = RED;
			}
		}
		else
		{
			uncle = grandparent->left;
			if (uncle && uncle->color == RED)
			{
				/* Case 1: Recolor */
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				node = grandparent;
			}
			else
			{
				if (node == parent->left)
				{
					/* Case 2: Right-Left */
					rotate_right(tree, parent);
					node = parent;
					parent = node->parent;
				}
				/* Case 3: Right-Right */
				rotate_left(tree, grandparent);
				parent->color = BLACK;
				grandparent->color = RED;
			}
		}
	}
	(*tree)->color = BLACK;
}

/**
 * rb_tree_insert - Inserts a value in a Red-Black Tree
 *
 * @tree: Pointer to the root node of the Red-Black tree
 * @value: Value to store in the new node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node;

	if (!tree)
		return (NULL);

	if (!*tree)
	{
		*tree = rb_tree_node(NULL, value, BLACK);
		return (*tree);
	}

	new_node = bst_insert(tree, value);
	if (!new_node)
		return (NULL);

	fix_violation(tree, new_node);
	return (new_node);
}
