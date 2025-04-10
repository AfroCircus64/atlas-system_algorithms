#include "heap.h"

void heapify_down(heap_t *heap, binary_tree_node_t *node);

/**
 * heap_extract - Extracts the root node from a heap
 *
 * @heap: Pointer to the heap
 *
 * Return: Pointer to the data of the extracted node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_node, *root;
	void *data;

	if (!heap || !heap->root)
		return (NULL);

	root = heap->root;
	data = root->data;

	if (heap->size == 1)
	{
		free(root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last_node = find_last_node(heap->root, heap->size);

	root->data = last_node->data;

	if (last_node->parent)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}
	free(last_node);

	heap->size--;

	heapify_down(heap, heap->root);

	return (data);
}


/**
 * heapify_down - Restores the Min Heap property by moving a node down
 *
 * @heap: Pointer to the heap
 * @node: Pointer to the node to heapify down
 */
void heapify_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest;

	if (!heap || !node)
		return;

	while (node->left || node->right)
	{
		smallest = node;

		if (node->left && heap->data_cmp(node->left->data, smallest->data) < 0)
			smallest = node->left;

		if (node->right && heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (smallest == node)
			break;

		swap_nodes(node, smallest);
		node = smallest;
	}
}
