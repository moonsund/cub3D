#include "cub3d.h"

static void	ft_normalize_map(t_map *map, int i);
static int	ft_store_map(t_map *map, int i);
static bool	ft_is_valid_pl_pos(const char **grid);
static bool	ft_is_valid_map(t_map *map);

int ft_process_map(t_map *map, int i)
{
	// looping throught the file to find first line of map
	while (ft_strchr(map->file_data[i], '1') == NULL
		|| ft_strchr(map->file_data[i], '1') == NULL)
	{
		if (map->file_data[i] == NULL)
			return (error_exit_msg("Empty map"), FAILURE);
		i++; // now i pointing to first line
	}
	if (ft_tabs_check(map, i) == false)
		return (error_exit_msg("Tabs are not allowed"), FAILURE);
	ft_normalize_map(map, i);
	// storing final map
	if (ft_store_map(map, i) == FAILURE)
		return (error_exit_msg("Map storing failed"), FAILURE);
	// check for player pos
	if (ft_is_valid_pl_pos(map->grid) == false)
		return (error_exit_msg("No player position"), FAILURE);
	// map validation
	if (ft_is_valid_map(map) == false)
		return (error_exit_msg("Invalid map"), FAILURE);
	return (SUCCESS);
}

static void	ft_normalize_map(t_map *map, int i)
{
	size_t	line_len;

	while (map->file_data[i])
	{
		line_len = ft_strlen(map->file_data[i]);
		printf("debug line len=[%zu]\n", ft_strlen(map->file_data[i]));
		if (line_len > map->map_width)
			map->map_width = line_len;
		map->map_height++;
		i++;
	}
}

static int	ft_store_map(t_map *map, int i)
{
	int		grid_row;

	grid_row = 0;
	map->grid = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->grid)
		return (FAILURE);
	while (map->file_data[i])
	{
		map->grid[grid_row] = ft_copy_grid_line(map, map->file_data[i]);
		grid_row++;
		i++;
	}
	map->grid[grid_row] = NULL;
	return (SUCCESS);
}

static bool	ft_is_valid_pl_pos(const char **grid)
{
	bool	flag;
	int		x;
	int		y;
	
	x = 0;
	y = 0;
	flag = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'N'
				|| grid[y][x] == 'S'
				|| grid[y][x] == 'E'
				|| grid[y][x] == 'W')
				flag += 1;
			x++;
		}
		y++;
	}
	if (flag != 1)
		return (false);
	return (true);
}

static bool	ft_is_valid_map(t_map *map)
{
	char	**grid_copy;
	bool	is_valid;

	ft_set_pl_pos(map);
	grid_copy = ft_copy_grid(map);
	if (grid_copy == NULL)
		return (false);
	is_valid = true;
	if (ft_flood_fill(map, grid_copy, map->pl_x, map->pl_y) == FAILURE)
		is_valid = false;
	ft_free_grid(grid_copy);
	return (is_valid);
}
