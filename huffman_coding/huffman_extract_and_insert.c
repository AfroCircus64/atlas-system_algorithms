#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes from the priority queue and
 * inserts a new node with their combined frequency
 *
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
	symbol_t *symbol;
	size_t combined_freq;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	node1 = heap_extract(priority_queue);
	node2 = heap_extract(priority_queue);

	if (!node1 || !node2)
		return (0);

	combined_freq = ((symbol_t *)node1->data)->freq + ((symbol_t *)node2->data)->freq;
	symbol = symbol_create(-1, combined_freq);

	if (!symbol)
	{
		free(node1);
		free(node2);
		return (0);
	}

	new_node = binary_tree_node(NULL, symbol);

	if (!new_node)
	{
		free(symbol);
		free(node1);
		free(node2);
		return (0);
	}

	new_node->left = node1;
	new_node->right = node2;
	node1->parent = new_node;
	node2->parent = new_node;

	if (!heap_insert(priority_queue, new_node))
	{
		free(symbol);
		free(new_node);
		return (0);
	}

	return (1);
}
