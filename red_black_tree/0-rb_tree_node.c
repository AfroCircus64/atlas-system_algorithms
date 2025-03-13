#include "rb_trees.h"

/**
 * rb_tree_node - Creates a new Red-Black tree node
 *
 * @parent: Pointer to the parent node
 * @value: Integer value to be stored in the new node
 * @color: Color of the new node (RED or BLACK)
 *
 * Return: Pointer to the newly created node, or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node = malloc(sizeof(rb_tree_t));

	if (!node)
		return (NULL);

	node->n = value;
	node->color = color;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;

	return (node);
}
