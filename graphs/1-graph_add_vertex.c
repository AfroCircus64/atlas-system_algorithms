#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to a graph
 * @graph: Pointer to the graph structure
 * @str: String to be stored in the vertex
 *
 * Return: Pointer to the new vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *temp;
	char *str_copy;

	if (!graph || !str)
	{
		return (NULL);
	}

	temp = graph->vertices;
	while (temp)
	{
		if (strcmp(temp->content, str) == 0)
			return (NULL);
		temp = temp->next;
	}

	str_copy = strdup(str);

	if (!str_copy)
	{
		return (NULL);
	}

	new_vertex = malloc(sizeof(vertex_t));

	if (!new_vertex)
	{
		free(str_copy);
		return (NULL);
	}

	new_vertex->content = str_copy;
	new_vertex->index = graph->nb_vertices;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!graph->vertices)
	{
		graph->vertices = new_vertex;
	}
	else
	{
		temp = graph->vertices;
		while (temp->next)
			temp = temp->next;
		temp->next = new_vertex;
	}

	graph->nb_vertices++;
	return (new_vertex);
}
