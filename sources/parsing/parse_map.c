#include "cub3d.h"

int parse_map_section(t_map *map, t_player *player, int start)
{
	skip_empty_lines(map->file_data, &start);
	if (start == map->lines_count)
		return (error_msg("process_map_data: missing map"));
	
	get_map_dimensions(map->file_data, &map->map_height, &map->map_width, start);

	if (check_trailing_content(map->file_data, start + map->map_height) == FAILURE)
		return (FAILURE);

	if (validate_map_chars(map->file_data, start) == FAILURE)
		return (FAILURE);

	if (build_map_grid(map, start) == FAILURE)
		return (FAILURE);

	if (find_player_position(player, map->grid) == FAILURE)
		return (FAILURE);

	if (validate_map_closure(map, player) == FAILURE)
		return (FAILURE);

	return (SUCCESS);
}

int	build_map_grid(t_map *map, int i)
{
	int		grid_row;

	grid_row = 0;
	map->grid = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->grid)
		return (error_errno("build_map_grid"));
	while (grid_row < map->map_height + 1)
		map->grid[grid_row++] = NULL;
	grid_row = 0;
	while (grid_row < map->map_height)
	{
		map->grid[grid_row] = copy_line(map->file_data[i], map->map_width);
		if (!map->grid[grid_row])
		{
			free_grid(map->grid);
			map->grid = NULL;
			return (FAILURE);
		}	
		grid_row++;
		i++;
	}
	map->grid[grid_row] = NULL;
	return (SUCCESS);
}

int find_player_position(t_player *player, char **grid)
{
	int	x;
	int	y;
	
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'N' || grid[y][x] == 'S'
				|| grid[y][x] == 'E' || grid[y][x] == 'W')
			{
				if (player->pl_dir == ' ')
					set_player_position(player, grid[y][x], y, x);
				else
					return (error_msg("find_player_position: multiple player positions"));
			}
			x++;
		}
		y++;
	}
	if (player->pl_dir == ' ')
		return (error_msg("find_player_position: missing player position"));
	return (SUCCESS);
}

int	validate_map_closure(t_map *map, t_player *player)
{
	char	**grid_copy;

	grid_copy = copy_grid(map);
	if (!grid_copy)
		return (FAILURE);
	if (flood_fill(map, grid_copy, player->pl_x, player->pl_y) == FAILURE)
	{
		free_grid(grid_copy);
		return (error_msg("validate_map_closure: map is not enclosed"));
	}
	free_grid(grid_copy);
	return (SUCCESS);
}

int	flood_fill(t_map *map, char **grid, int x, int y)
{
	// check if we passed over the grid
	if (y < 0 || y >= map->map_height)
		return (FAILURE);
	if (x < 0 || x >= map->map_width)
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
	if (flood_fill(map, grid, x + 1, y) == FAILURE
		|| flood_fill(map, grid, x - 1, y) == FAILURE
		|| flood_fill(map, grid, x, y + 1) == FAILURE
		|| flood_fill(map, grid, x, y - 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}


