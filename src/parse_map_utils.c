#include "cub3d.h"

char *ft_copy_grid_line(t_map *map, char *src)
{
	char	*dest;
	size_t	i;

	dest = malloc(sizeof(char) * (map->map_width + 1));
	if (!dest)
		return (NULL); 
	i = 0;
	while (src[i] && src[i] != '\n' && i < map->map_width)
	{
		dest[i] = src[i];
		i++;
	}
	while(i < map->map_width)
		dest[i++] = ' ';
	dest[i] = '\0';
	return (dest);
}

void	ft_set_pl_pos(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'N'
				|| map->grid[y][x] == 'S'
				|| map->grid[y][x] == 'E'
				|| map->grid[y][x] == 'W')
				{
					map->pl_dir = map->grid[y][x];
					map->pl_x = x;
					map->pl_y = y;
					break;
				}
			x++;
		}
		y++;
	}
}

char **ft_copy_grid(t_map *map)
{
	char	**temp_grid;
	int		i;

	i = 0;
	temp_grid = malloc(sizeof(char *) * (map->map_height + 1));
	if (!temp_grid)
		return (NULL);
	while (map->grid[i])
	{
		temp_grid[i] = ft_strdup(map->grid[i]);
			if (!temp_grid[i])
				return (ft_free_grid(temp_grid), NULL);
		i++;
	}
	temp_grid[i] = NULL;
	return (temp_grid);
}

void	ft_free_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
		if (grid[i] != NULL)
			free(grid[i]);
	if (grid != NULL)
		free(grid);
}

int	ft_flood_fill(t_map *map, char **grid, int x, int y)
{
	// check if we passed over the grid
	if (y < 0 || y >= (int)map->map_height)
		return (FAILURE);
	if ( x < 0 || x >= (int)ft_strlen(grid[y]))
		return (FAILURE);
	// if we meet space
	if (grid[y][x] == ' ')
		return (FAILURE);
	// if it's a wall, all good, return back
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (SUCCESS);
	// setting as 'V' - visited
	grid[y][x] = 'V';
	// Recursion
	if (ft_flood_fill(map, grid, x + 1, y) == FAILURE
		|| ft_flood_fill(map, grid, x - 1, y) == FAILURE
		|| ft_flood_fill(map, grid, x, y + 1) == FAILURE
		|| ft_flood_fill(map, grid, x, y - 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
