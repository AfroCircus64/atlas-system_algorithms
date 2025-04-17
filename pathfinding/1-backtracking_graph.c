#include "pathfinding.h"

int graph_backtrack(vertex_t const *vertex, vertex_t const *target,
	int *visited, queue_t *path);

/**
 * backtracking_graph - Finds a path in a graph using backtracking
 *
 * @graph: The graph to search
 * @start: The starting vertex
 * @target: The target vertex
 *
 * Return: A queue containing the path from start to target, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	 vertex_t const *target)
{
	queue_t *path;
	int *visited;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}

	if (!graph_backtrack(start, target, visited, path))
	{
		queue_delete(path);
		path = NULL;
	}

	free(visited);
	return (path);
}

/**
 * graph_backtrack - Recursive helper function to find the path
 *
 * @vertex: The current vertex
 * @target: The target vertex
 * @visited: Array to track visited vertices
 * @path: Queue to store the path
 *
 * Return: 1 if the path is found, 0 otherwise
 */
int graph_backtrack(vertex_t const *vertex, vertex_t const *target,
	int *visited, queue_t *path)
{
	edge_t *edge;
	char *content_copy;

	if (!vertex || visited[vertex->index])
		return (0);

	printf("Checking %s\n", vertex->content);
	visited[vertex->index] = 1;

	content_copy = strdup(vertex->content);
	if (!content_copy)
		return (0);

	if (!queue_push_back(path, content_copy))
	{
		free(content_copy);
		return (0);
	}

	if (vertex == target)
		return (1);

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		if (graph_backtrack(edge->dest, target, visited, path))
			return (1);
	}

	free(dequeue(path));
	return (0);
}
