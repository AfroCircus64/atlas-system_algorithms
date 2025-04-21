#include "nary_trees.h"

size_t calculate_diameter(const nary_tree_t *node, size_t *diameter);

/**
 * nary_tree_diameter - Computes the diameter of an N-ary tree
 *
 * @root: Pointer to the root node of the N-ary tree
 *
 * Return: The diameter of the N-ary tree, or 0 if the tree is empty
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	if (!root)
	{
		return (0);
	}

	calculate_diameter(root, &diameter);
	return (diameter + 1);
}

/**
 * calculate_diameter - Function to compute the diameter of an N-ary tree
 *
 * @node: Pointer to the current node
 * @diameter: Pointer to store the maximum diameter found
 *
 * Return: The height of the current node
 */
size_t calculate_diameter(const nary_tree_t *node, size_t *diameter)
{
	size_t max_height1 = 0, max_height2 = 0, child_height;
	nary_tree_t *child;

	if (!node)
	{
		return (0);
	}

	/* Traverse all children to find the two largest heights */
	for (child = node->children; child; child = child->next)
	{
		child_height = calculate_diameter(child, diameter);

		if (child_height > max_height1)
		{
			max_height2 = max_height1;
			max_height1 = child_height;
		}
		else if (child_height > max_height2)
		{
			max_height2 = child_height;
		}
	}

	/* Update the diameter if the current path is longer */
	if (max_height1 + max_height2 > *diameter)
	{
		*diameter = max_height1 + max_height2;
	}

	/* Return the height of the current node */
	return (max_height1 + 1);
}
