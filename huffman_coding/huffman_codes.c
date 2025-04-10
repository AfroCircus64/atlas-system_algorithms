#include "huffman.h"

/**
 * huffman_codes - Generates the Huffman codes for the characters
 *
 * @data: Array of characters
 * @freq: Array of frequencies
 * @size: Size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[256];

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);

	if (!root)
		return (0);

	print_huffman_codes(root, code, 0);

	heap_delete((heap_t *)root, free);

	return (1);
}


/**
 * print_huffman_codes - Recursively traverses the Huffman tree to print codes
 *
 * @node: Pointer to the current node in the Huffman tree
 * @code: Array to store the current Huffman code
 * @depth: Current depth in the tree (used as the index for the code array)
 */
void print_huffman_codes(binary_tree_node_t *node, char *code, int depth)
{
	symbol_t *symbol;

	if (!node)
		return;

	if (!node->left && !node->right)
	{
		symbol = (symbol_t *)node->data;
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
		return;
	}

	code[depth] = '0';
	print_huffman_codes(node->left, code, depth + 1);

	code[depth] = '1';
	print_huffman_codes(node->right, code, depth + 1);
}
