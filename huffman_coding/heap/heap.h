#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

/* DATA STRUCTURES */

/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/**
 * struct queue_node_s - Queue node data structure
 *
 * @vertex: Pointer to a binary tree node
 * @next: Pointer to the next queue node
 */
typedef struct queue_node_s
{
	binary_tree_node_t *vertex;
	struct queue_node_s *next;
} queue_node_t;


/* FUNCTION PROTOTYPES */
heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
void *heap_extract(heap_t *heap);
void heap_delete(heap_t *heap, void (*free_data)(void *));

/* HELPER FUNCTIONS */
binary_tree_node_t *find_last_node(binary_tree_node_t *root, size_t size);
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2);
int enqueue(queue_node_t **queue, binary_tree_node_t *node);
queue_node_t *dequeue(queue_node_t **queue);


#endif /* HEAP_H */
