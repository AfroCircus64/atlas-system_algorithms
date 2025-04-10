#include "heap.h"

void heapify_up(heap_t *heap, binary_tree_node_t *node);

/**
 * heap_insert - Inserts a node into a heap
 *
 * @heap: Pointer to the heap
 * @data: Pointer to the data to be inserted
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *last_node;

	if (!heap || !data)
		return (NULL);

	if (!heap->root)
	{
		heap->root = binary_tree_node(NULL, data);
		if (!heap->root)
			return (NULL);
		heap->size++;
		return (heap->root);
	}

	last_node = find_last_node(heap->root, heap->size + 1);

	if (!last_node)
		return (NULL);

	new_node = binary_tree_node(last_node, data);

	if (!new_node)
		return (NULL);

	if (!last_node->left)
	{
		last_node->left = new_node;
	}
	else
	{
		last_node->right = new_node;
	}

	heap->size++;

	heapify_up(heap, new_node);

	return (new_node);
}


/**
 * heapify_up - Restores the Min Heap property by moving a node up
 *
 * @heap: Pointer to the heap
 * @node: Pointer to the node to heapify up
 */
void heapify_up(heap_t *heap, binary_tree_node_t *node)
{
	if (!heap || !node)
		return;

	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		swap_nodes(node, node->parent);
		node = node->parent;
	}
}
