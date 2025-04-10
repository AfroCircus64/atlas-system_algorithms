#include "huffman.h"
#include "heap/heap.h"

int symbol_cmp(void *a, void *b);

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 *
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the created priority queue
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *priority_queue;
	binary_tree_node_t *node;
	symbol_t *symbol;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = heap_create(symbol_cmp);

	if (!priority_queue)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);

		if (!symbol)
		{
			heap_delete(priority_queue, NULL);
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);

		if (!node)
		{
			free(symbol);
			heap_delete(priority_queue, NULL);
			return (NULL);
		}

		if (!heap_insert(priority_queue, node))
		{
			free(symbol);
			free(node);
			heap_delete(priority_queue, NULL);
			return (NULL);
		}
	}

	return (priority_queue);
}


/**
 * symbol_cmp - Compares two symbols based on their frequency
 *
 * @a: Pointer to the first symbol
 * @b: Pointer to the second symbol
 *
 * Return: Difference between the frequencies of the two symbols
 */
int symbol_cmp(void *a, void *b)
{
	binary_tree_node_t *node_a = (binary_tree_node_t *)a;
	binary_tree_node_t *node_b = (binary_tree_node_t *)b;

	symbol_t *symbol_a = (symbol_t *)node_a->data;
	symbol_t *symbol_b = (symbol_t *)node_b->data;

	return (symbol_a->freq - symbol_b->freq);
}
