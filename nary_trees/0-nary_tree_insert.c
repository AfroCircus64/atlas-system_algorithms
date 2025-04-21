#include "nary_trees.h"

/**
 * nary_tree_insert - Inserts a new node in the N-ary tree
 *
 * @parent: Pointer to the parent node where the new node will be inserted
 * @str: String content for the new node
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node;

	if (!str)
	{
		return (NULL);
	}

	new_node = malloc(sizeof(nary_tree_t));

	if (!new_node)
	{
		return (NULL);
	}

	new_node->content = strdup(str);

	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}

	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;

	if (parent)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children++;
	}

	return (new_node);
}
