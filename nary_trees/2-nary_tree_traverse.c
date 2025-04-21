#include "nary_trees.h"

size_t nary_tree_traverse_helper(nary_tree_t const *node,
	void (*action)(nary_tree_t const *node, size_t depth), size_t depth);

/**
 * nary_tree_traverse - Traverses an N-ary tree
 *
 * @root: Pointer to the root node of the tree
 * @action: Function pointer to the action to be applied to each node
 *
 * Return: The number of nodes traversed
 */
size_t nary_tree_traverse(nary_tree_t const *root,
	 void (*action)(nary_tree_t const *node, size_t depth))
{
	size_t max_depth = 0, child_depth;
	nary_tree_t *child;

	if (!root || !action)
	{
		return (0);
	}

	/* Apply the action to the current node */
	action(root, 0);

	/* Traverse the children */
	for (child = root->children; child; child = child->next)
	{
		child_depth = nary_tree_traverse_helper(child, action, 1);

		if (child_depth > max_depth)
		{
			max_depth = child_depth;
		}
	}

	return (max_depth + 1);
}


/**
 * nary_tree_traverse_helper - Helper function for recursive traversal
 *
 * @node: Pointer to the current node
 * @action: Function pointer to the action to be applied to each node
 * @depth: Current depth of the node
 *
 * Return: The maximum depth encountered during traversal
 */
size_t nary_tree_traverse_helper(nary_tree_t const *node,
	void (*action)(nary_tree_t const *node, size_t depth), size_t depth)
{
	size_t max_depth = depth, child_depth;
	nary_tree_t *child;

	if (!node)
	{
		return (depth);
	}

	/* Apply the action to the current node */
	action(node, depth);

	/* Traverse the children */
	for (child = node->children; child; child = child->next)
	{
		child_depth = nary_tree_traverse_helper(child, action, depth + 1);

		if (child_depth > max_depth)
		{
			max_depth = child_depth;
		}
	}

	return (max_depth);
}
