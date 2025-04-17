#include "pathfinding.h"

int backtrack(char **map, int rows, int cols, int x, int y,
	point_t const *target, queue_t *path);

/**
 * backtracking_array - Finds a path in a 2D array using backtracking
 * @map: The 2D array representing the map
 * @rows: The number of rows in the map
 * @cols: The number of columns in the map
 * @start: The starting point
 * @target: The target point
 *
 * Return: A queue containing the path from start to target, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows,
	 int cols, point_t const *start, point_t const *target)
	{
		queue_t *path;

		if (!map || !start || !target || rows <= 0 || cols <= 0)
			return (NULL);

		path = queue_create();
		if (!path)
			return (NULL);

		if (!backtrack(map, rows, cols, start->x, start->y, target, path))
		{
			queue_delete(path);
			return (NULL);
		}

		return (path);
	}


/**
 * backtrack - Recursive helper function to find the path
 * @map: The 2D array representing the map
 * @rows: The number of rows in the map
 * @cols: The number of columns in the map
 * @x: Current x-coordinate
 * @y: Current y-coordinate
 * @target: The target point
 * @path: Queue to store the path
 *
 * Return: 1 if the path is found, 0 otherwise
 */
int backtrack(char **map, int rows, int cols, int x, int y,
	point_t const *target, queue_t *path)
{
	point_t *point;

	if (x < 0 || x >= rows || y < 0 || y >= cols || map[x][y] != '0')
	return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);

	map[x][y] = '2'; /* Mark the cell as visited */

	point = malloc(sizeof(point_t));
	if (!point)
	return (0);

	point->x = x;
	point->y = y;
	queue_push_back(path, point);

	if (x == target->x && y == target->y)
	return (1);

	/* Explore neighbors in the order: RIGHT, BOTTOM, LEFT, TOP */
	if (backtrack(map, rows, cols, x, y + 1, target, path) ||
	backtrack(map, rows, cols, x + 1, y, target, path) ||
	backtrack(map, rows, cols, x, y - 1, target, path) ||
	backtrack(map, rows, cols, x - 1, y, target, path))
	return (1);

	/* Backtrack: Remove the point from the path */
	free(dequeue(path));
	return (0);
}
