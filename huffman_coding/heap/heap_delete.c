#include "heap.h"

void free_tree(binary_tree_node_t *node, void (*free_data)(void *));

/**
 * heap_delete - Deletes a heap and frees its memory
 *
 * @heap: Pointer to the heap to be deleted
 * @free_data: Function to free the data stored in the nodes
 *
 * Return: None
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
	{
		return;
	}

	free_tree(heap->root, free_data);

	free(heap);
}


/**
 * free_tree - Recursively frees the nodes of a binary tree
 *
 * @node: Pointer to the current node
 * @free_data: Function to free the data stored in the node
 */
void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	free_tree(node->left, free_data);
	free_tree(node->right, free_data);

	if (free_data)
		free_data(node->data);

	free(node);
}
