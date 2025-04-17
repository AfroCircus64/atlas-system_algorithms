#include "pathfinding.h"

int find_min_distance(int *distances, int *visited, size_t size);
queue_t *build_path(int *predecessors, int target_index, vertex_t **vertices);

/**
 * dijkstra_graph - Finds the shortest path in a graph
 * @graph: The graph to search
 * @start: The starting vertex
 * @target: The target vertex
 *
 * Return: A queue containing the path from start to target, or NULL on failure
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	 vertex_t const *target)
{
	int *distances, *visited, *predecessors;
	vertex_t **vertices;
	size_t i;
	edge_t *edge;
	int current_index, neighbor_index;
	queue_t *path = NULL;

	if (!graph || !start || !target)
		return (NULL);

	distances = malloc(sizeof(int) * graph->nb_vertices);
	visited = calloc(graph->nb_vertices, sizeof(int));
	predecessors = malloc(sizeof(int) * graph->nb_vertices);
	vertices = malloc(sizeof(vertex_t *) * graph->nb_vertices);

	if (!distances || !visited || !predecessors || !vertices)
		goto cleanup;

	for (i = 0; i < graph->nb_vertices; i++)
	{
		distances[i] = INT_MAX;
		predecessors[i] = -1;
		vertices[i] = NULL;
	}

	for (vertex_t *v = graph->vertices; v; v = v->next)
		vertices[v->index] = v;

	distances[start->index] = 0;

	while ((current_index = find_min_distance(distances, visited, graph->nb_vertices)) != -1)
	{
		visited[current_index] = 1;
		printf("Checking %s, distance from %s is %d\n",
				vertices[current_index]->content, start->content, distances[current_index]);

		if (vertices[current_index] == target)
		{
			path = build_path(predecessors, target->index, vertices);
			break;
		}

		for (edge = vertices[current_index]->edges; edge; edge = edge->next)
		{
			neighbor_index = edge->dest->index;
			if (!visited[neighbor_index] &&
				distances[current_index] + edge->weight < distances[neighbor_index])
			{
				distances[neighbor_index] = distances[current_index] + edge->weight;
				predecessors[neighbor_index] = current_index;
			}
		}
	}

	free(distances);
	free(visited);
	free(predecessors);
	free(vertices);

	return (path);
}


/**
 * find_min_distance - Finds the vertex with the minimum distance
 * @distances: Array of distances
 * @visited: Array of visited vertices
 * @size: Number of vertices
 *
 * Return: Index of the vertex with the minimum distance
 */
int find_min_distance(int *distances, int *visited, size_t size)
{
	int min = INT_MAX, min_index = -1;
	size_t i;

	for (i = 0; i < size; i++)
	{
		if (!visited[i] && distances[i] < min)
		{
			min = distances[i];
			min_index = i;
		}
	}

	return (min_index);
}

/**
 * build_path - Builds the path from the predecessors array
 * @predecessors: Array of predecessors
 * @target_index: Index of the target vertex
 * @vertices: Array of vertices
 *
 * Return: Queue containing the path
 */
queue_t *build_path(int *predecessors, int target_index, vertex_t **vertices)
{
	queue_t *path = queue_create();
	char *content_copy;

	if (!path)
		return (NULL);

	while (target_index != -1)
	{
		content_copy = strdup(vertices[target_index]->content);
		if (!content_copy || !queue_push_front(path, content_copy))
		{
			free(content_copy);
			queue_delete(path);
			return (NULL);
		}
		target_index = predecessors[target_index];
	}

	return (path);
}
