#include "graphs.h"

/**
 * graph_add_edge - Adds an edge to a graph
 * @graph: Pointer to the graph structure
 * @src: String of the source vertex
 * @dest: String of the destination vertex
 * @type: Type of the edge (unidirectional or bidirectional)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
	vertex_t *src_vertex = NULL, *dest_vertex = NULL;
	edge_t *new_edge = NULL, *temp_edge = NULL;

	if (!graph || !src || !dest || (type != UNIDIRECTIONAL && type != BIDIRECTIONAL))
		return (0);

	src_vertex = graph->vertices;

	while (src_vertex && strcmp(src_vertex->content, src) != 0)
		src_vertex = src_vertex->next;

	dest_vertex = graph->vertices;

	while (dest_vertex && strcmp(dest_vertex->content, dest) != 0)
		dest_vertex = dest_vertex->next;

	if (!src_vertex || !dest_vertex)
		return (0);

	new_edge = malloc(sizeof(edge_t));

	if (!new_edge)
		return (0);

	new_edge->dest = dest_vertex;
	new_edge->next = NULL;

	if (!src_vertex->edges)
	{
		src_vertex->edges = new_edge;
	}
	else
	{
		temp_edge = src_vertex->edges;
		while (temp_edge->next)
			temp_edge = temp_edge->next;
		temp_edge->next = new_edge;
	}

	if (type == BIDIRECTIONAL)
	{
		new_edge = malloc(sizeof(edge_t));
		if (!new_edge)
			return (0);
		new_edge->dest = src_vertex;
		new_edge->next = NULL;

		if (!dest_vertex->edges)
			dest_vertex->edges = new_edge;
		else
		{
			temp_edge = dest_vertex->edges;
			while (temp_edge->next)
				temp_edge = temp_edge->next;
			temp_edge->next = new_edge;
		}
	}

	return (1);
}
