#include "heap.h"

/**
 * find_last_node - Finds the last node in a binary heap
 *
 * @root: Pointer to the root node of the heap
 * @size: Size of the heap
 *
 * Return: Pointer to the last node, or NULL if the heap is empty
 */
binary_tree_node_t *find_last_node(binary_tree_node_t *root, size_t size)
{
	queue_node_t *queue = NULL, *node;
	binary_tree_node_t *last_node = NULL;

	if (!root || size == 0)
		return (NULL);

	enqueue(&queue, root);

	while (queue)
	{
		node = dequeue(&queue);
		last_node = node->vertex;

		if (last_node->left)
			enqueue(&queue, last_node->left);
		if (last_node->right)
			enqueue(&queue, last_node->right);

		free(node);
	}

	return (last_node);
}


/**
 * swap_nodes - Swaps the data of two binary tree nodes
 *
 * @node1: Pointer to the first node
 * @node2: Pointer to the second node
 */
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *temp;

	if (!node1 || !node2)
		return;

	temp = node1->data;
	node1->data = node2->data;
	node2->data = temp;
}



/**
 * enqueue - Adds a node to the queue
 *
 * @queue: Double pointer to the queue
 * @node: Pointer to the binary tree node to enqueue
 *
 * Return: 1 on success, 0 on failure
 */
int enqueue(queue_node_t **queue, binary_tree_node_t *node)
{
	queue_node_t *new_node, *temp;

	new_node = malloc(sizeof(queue_node_t));
	if (!new_node)
		return (0);

	new_node->vertex = node;
	new_node->next = NULL;

	if (!*queue)
		*queue = new_node;
	else
	{
		temp = *queue;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}

	return (1);
}

/**
 * dequeue - Removes a node from the queue
 *
 * @queue: Double pointer to the queue
 *
 * Return: Pointer to the dequeued node, or NULL if the queue is empty
 */
queue_node_t *dequeue(queue_node_t **queue)
{
	queue_node_t *node;

	if (!*queue)
		return (NULL);

	node = *queue;
	*queue = (*queue)->next;

	return (node);
}
