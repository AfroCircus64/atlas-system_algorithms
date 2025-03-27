#include "graphs.h"

/**
 * queue_node_t - Node structure for the queue
 * @vertex: Pointer to the vertex
 * @depth: Depth of the vertex
 * @next: Pointer to the next node in the queue
 */
typedef struct queue_node_s
{
	const vertex_t *vertex;
	size_t depth;
	struct queue_node_s *next;
} queue_node_t;

/**
 * enqueue - Adds a vertex to the queue
 * @queue: Double pointer to the queue
 * @vertex: Pointer to the vertex to enqueue
 * @depth: Depth of the vertex
 *
 * Return: 1 on success, 0 on failure
 */
int enqueue(queue_node_t **queue, const vertex_t *vertex, size_t depth)
{
	queue_node_t *new_node, *temp;

	new_node = malloc(sizeof(queue_node_t));

	if (!new_node)
		return (0);

	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	if (!*queue)
	{
		*queue = new_node;
	}
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
 * dequeue - Removes a vertex from the queue
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

/**
 * breadth_first_traverse - Traverses a graph in breadth-first order
 * @graph: Pointer to the graph to traverse
 * @action: Function pointer to the action to perform on each vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	queue_node_t *queue = NULL, *node;
	edge_t *edge;
	size_t max_depth = 0;

	if (!graph || !action || !graph->vertices)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));

	if (!visited)
		return (0);

	enqueue(&queue, graph->vertices, 0);
	visited[graph->vertices->index] = 1;

	while (queue)
	{
		node = dequeue(&queue);
		action(node->vertex, node->depth);

		if (node->depth > max_depth)
			max_depth = node->depth;

		for (edge = node->vertex->edges; edge; edge = edge->next)
		{
			if (!visited[edge->dest->index])
			{
				enqueue(&queue, edge->dest, node->depth + 1);
				visited[edge->dest->index] = 1;
			}
		}

		free(node);
	}

	free(visited);
	return (max_depth);
}
