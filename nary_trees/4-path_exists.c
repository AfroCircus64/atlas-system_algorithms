#include "nary_trees.h"

/**
 * path_exists - Checks if a path exists in an N-ary tree
 *
 * @root: Pointer to the root node of the N-ary tree
 * @path: Array of strings representing the path to check
 *
 * Return: 1 if the path exists, 0 if it does not, or -1 on error
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	const nary_tree_t *current = root;
	size_t i;

	if (!root || !path || !*path)
	{
		return (0);
	}

	if (strcmp(current->content, path[0]) != 0)
	{
		return (0);
	}

	for (i = 0; path[i]; i++)
	{
		if (!path[i + 1])
		{
			return (1);
		}

		nary_tree_t *child = current->children;
		int found = 0;

		while (child)
		{
			if (strcmp(child->content, path[i + 1]) == 0)
			{
				current = child;
				found = 1;
				break;
			}
			child = child->next;
		}

		if (!found)
		{
			return (0);
		}
	}
	return (1);
}
