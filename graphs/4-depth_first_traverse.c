#include "graphs.h"

/**
 * dfs_helper - Helper function for depth-first traversal
 * @vertex: Pointer to the current vertex
 * @visited: Array to track visited vertices
 * @depth: Current depth of traversal
 * @action: Function pointer to the action to perform on each vertex
 *
 * Return: The maximum depth encountered during traversal
 */
size_t dfs_helper(const vertex_t *vertex, int *visited, size_t depth, void (*action)(const vertex_t *v, size_t depth))
{
	edge_t *edge;
	size_t max_depth = depth, temp_depth;

	if (!vertex || visited[vertex->index])
	{
		return (depth);
	}

	visited[vertex->index] = 1;
	action(vertex, depth);

	for (edge = vertex->edges; edge; edge = edge->next)
	{
		temp_depth = dfs_helper(edge->dest, visited, depth + 1, action);

		if (temp_depth > max_depth)
		{
			max_depth = temp_depth;
		}
	}

	return (max_depth);
}

/**
* depth_first_traverse - Traverses a graph in depth-first order
* @graph: Pointer to the graph to traverse
* @action: Function pointer to the action to perform on each vertex
*
* Return: The biggest vertex depth, or 0 on failure
*/
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_depth = 0;

	if (!graph || !action || !graph->vertices)
	{
		return (0);
	}

	visited = calloc(graph->nb_vertices, sizeof(int));

	if (!visited)
	{
		return (0);
	}

	max_depth = dfs_helper(graph->vertices, visited, 0, action);

	free(visited);

	return (max_depth);
}
