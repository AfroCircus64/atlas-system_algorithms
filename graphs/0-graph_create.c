#include "graphs.h"

/**
 * graph_create - Allocates memory for a graph_t structure and initializes it
 *
 * Return: Pointer to the allocated graph_t structure, or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(graph_t));

	if (!graph)
	{
		return (NULL);
	}

	graph->vertices = NULL;
	graph->nb_vertices = 0;

	return (graph);
}
