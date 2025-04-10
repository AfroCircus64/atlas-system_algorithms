#include "huffman.h"

/**
 * symbol_create - Creates a new symbol
 *
 * @data: The character
 * @freq: The associated frequency
 *
 * Return: A pointer to the new symbol, or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	symbol = malloc(sizeof(symbol_t));

	if (!symbol)
	{
		return (NULL);
	}

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
