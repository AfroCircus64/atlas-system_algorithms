#include "heap.h"

/**
 * binary_tree_node - Creates a binary tree node
 *
 * @parent: Pointer to the parent node
 * @data: Pointer to the data to be stored in the node
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node;

	node = malloc(sizeof(binary_tree_node_t));

	if (!node)
	{
		return (NULL);
	}

	node->data = data;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	return (node);
}
