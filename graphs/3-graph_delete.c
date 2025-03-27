#include "graphs.h"

/**
 * graph_delete - Deletes a graph and frees all its memory
 * @graph: Pointer to the graph to delete
 *
 * Return: Nothing
 */
void graph_delete(graph_t *graph)
{
	vertex_t *vertex, *temp_vertex;
	edge_t *edge, *temp_edge;

	if (!graph)
		return;

	vertex = graph->vertices;

	while (vertex)
	{
		edge = vertex->edges;

		while (edge)
		{
			temp_edge = edge->next;
			free(edge);
			edge = temp_edge;
		}

		temp_vertex = vertex->next;
		free(vertex->content);
		free(vertex);
		vertex = temp_vertex;
	}
	free(graph);
}
