#include "nary_trees.h"

/**
 * nary_tree_delete - Deletes an N-ary tree
 *
 * @tree: Pointer to the root node of the tree to be deleted
 *
 * Return: NULL
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child, *next_child;

	if (!tree)
	{
		return;
	}

	/* Recursively delete all children */
	child = tree->children;

	while (child)
	{
		next_child = child->next;
		nary_tree_delete(child);
		child = next_child;
	}

	/* Free the content and the node itself */
	free(tree->content);
	free(tree);
}
