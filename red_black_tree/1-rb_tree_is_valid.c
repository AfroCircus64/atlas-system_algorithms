#include "rb_trees.h"

/**
 * is_bst - Checks if a binary tree is a valid Binary Search Tree (BST)
 *
 * @tree: Pointer to the root node of the tree to check
 * @min: Minimum value allowed for the current node
 * @max: Maximum value allowed for the current node
 *
 * Return: 1 if the tree is a valid BST, 0 otherwise
 */
int is_bst(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
	{
		return (1);
	}

	if (tree->n <= min || tree->n >= max)
	{
		return (0);
	}

	return (is_bst(tree->left, min, tree->n) &&
		is_bst(tree->right, tree->n, max));
}

/**
 * check_height - Checks if all paths from root to leaves have the same
 *                      number of black nodes
 *
 * @tree: Pointer to the root node of the tree to check
 * @count: Current count of black nodes
 * @path_count: Pointer to store the black node count of a path
 *
 * Return: 1 if all paths have the same black node count, 0 otherwise
 */
int check_height(const rb_tree_t *tree, int count, int *path_count)
{
	if (!tree)
	{
		if (*path_count == -1)
		{
			*path_count = count;
			return (1);
		}
		return (count == *path_count);
	}

	if (tree->color == BLACK)
	{
		count++;
	}

	return (check_height(tree->left, count, path_count) &&
		check_height(tree->right, count, path_count));
}

/**
 * rb_tree_is_valid - Checks if a binary tree is a valid Red-Black Tree
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int path_count = -1;

	if (!tree)
	{
		return (0);
	}

	if (tree->color != BLACK)
	{
		return (0);
	}

	if (!is_bst(tree, INT_MIN, INT_MAX))
	{
		return (0);
	}

	if (tree->color == RED)
	{
		if ((tree->left && tree->left->color == RED) ||
			(tree->right && tree->right->color == RED))
			return (0);
	}

	if (!check_height(tree, 0, &path_count))
	{
		return (0);
	}

	return (1);
}
