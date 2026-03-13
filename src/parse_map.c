#include "cub3d.h"

bool	ft_forbid_and_double_check(t_map *map, int i);
bool	ft_player_pos_char(char input);
int		ft_skip_empty_lines(t_map *map, int *i);
int		ft_get_height_and_valid_end(t_map *map, int i);
int		ft_check_garbage(t_map *map, int i);
void	ft_normalize_map(t_map *map, int i);
int		ft_store_map(t_map *map, int i);
bool	ft_is_valid_map(t_map *map);
char 	*ft_copy_grid_line(t_map *map, char *src);
bool	ft_get_pl_pos(t_map *map, const char **grid);
char 	**ft_copy_grid(t_map *map);
void	ft_free_grid(char **grid);
int		ft_flood_fill(t_map *map, char **grid, int x, int y);

int ft_process_map(t_map *map, int i)
{
	// check rest of the file for forbidden chars
	if (ft_forbid_and_double_check(map, i) == FAILURE)
		return (FAILURE);
	
	// get to the map start
	if (ft_skip_empty_lines(map, &i) == FAILURE)
		return (FAILURE);

	// Get map height and check for pieces after map end
	if (ft_get_height_and_valid_end(map, i) == FAILURE)
		return (FAILURE);

	ft_normalize_map(map, i);

	// storing final map
	if (ft_store_map(map, i) == FAILURE)
		return (FAILURE);

	// check for player pos
	if (ft_get_pl_pos(map, map->grid) == false)
		return (FAILURE);

	// map validation
	if (ft_is_valid_map(map) == false)
		return (FAILURE);
	return (SUCCESS);
}

bool	ft_forbid_and_double_check(t_map *map, int i)
{
	char	*line;
	int		j;
	int		pl_pos;

	pl_pos = 0;
	while (map->file_data[i])
	{
		line = map->file_data[i];
		j = 0;
		while (line[j])
		{
			if (ft_pl_pos_char(line[j]) == true)
				if (pl_pos++ > 1)
					return (error_exit_msg("Multiple player positions"), false);
			if (!(line[j] == 'N' || line[j] == 'S'
				|| line[j] == 'E' || line[j] == 'W'
				|| line[j] == '0' || line[j] == '1'
				|| line[j] == ' ' || line[j] == '\n'))
					return (error_exit_msg("Forbidden chars"), false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	ft_player_pos_char(char input)
{
	if (input == 'N' || input == 'S'
		|| input == 'W' ||input == 'E')
		return (true);
	return (false);
}

int	ft_skip_empty_lines(t_map *map, int *i)
{
	int		j;
	char	*line;

	while (map->file_data[*i])
	{
		j = 0;
		line = map->file_data[*i];
		while(line[j])
		{
			if (line[j] != ' ' && line[j] != '\n')
				return (SUCCESS);
			j++;
		}
		(*i)++;
	}
	return (error_exit_msg("Empty map"));
}

int	ft_get_height_and_valid_end(t_map *map, int i)
{
	char	*line;
	int		height;

	height = 1;
	while (map->file_data[i])
	{
		line = map->file_data[i];
		if (!(ft_strchr(line, '1') || ft_strchr(line, '0')
			|| ft_strchr(line, 'N') || ft_strchr(line, 'S')
			|| ft_strchr(line, 'E') || ft_strchr(line, 'W')))
		{
			map->map_height = height - 1;
			break ;
		}
		height++;
		i++;
	}
	if (ft_check_garbage(map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_garbage(t_map *map, int i)
{
	char	*line;
	int		j;

	while (map->file_data[i])
	{
		j = 0;
		line = map->file_data[i];
		while (line[j])
		{
			if (!(line[j] == ' ' || line[j] == '\n'
				|| line[j] == '\0'))
			{
				error_exit_msg("Map gap");
				return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

void	ft_normalize_map(t_map *map, int i)
{
	size_t	line_len;
	int		j;

	j = 0;
	while (j < map->map_height)
	{
		line_len = ft_strlen(map->file_data[i]);
		if (line_len > map->map_width)
			map->map_width = line_len;
		i++;
		j++;
	}
}

int	ft_store_map(t_map *map, int i)
{
	int		grid_row;

	grid_row = 0;
	map->grid = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->grid)
	{
		error_exit_msg("Map storing failed");
		return (error_errno("ft_store_map grid"));
	}
	while (grid_row < map->map_height)
	{
		map->grid[grid_row] = ft_copy_grid_line(map, map->file_data[i]);
		if (!map->grid[grid_row])
		{
			error_exit_msg("Map storing failed");
			return (error_errno("ft_store_map height"));
		}
		grid_row++;
		i++;
	}
	map->grid[grid_row] = NULL;
	return (SUCCESS);
}

bool	ft_get_pl_pos(t_map *map, const char **grid)
{
	int	flag;
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'N' || grid[y][x] == 'S'
				|| grid[y][x] == 'E' || grid[y][x] == 'W')
			{
				ft_set_pl_pos(map, grid[y][x], x, y);
				return (true);
			}
			x++;
		}
		y++;
	}
	return (error_exit_msg("No player position"), false);
}

void	ft_set_pl_pos(t_map *map, char c, int x, int y)
{
	map->pl_dir = c;
	map->pl_x = x;
	map->pl_y = y;
}

bool	ft_is_valid_map(t_map *map)
{
	char	**grid_copy;
	bool	is_valid;

	grid_copy = ft_copy_grid(map);
	if (grid_copy == NULL)
		return (error_exit_msg("Invalid map"), false);
	is_valid = true;
	if (ft_flood_fill(map, grid_copy, map->pl_x, map->pl_y) == FAILURE)
	{
		is_valid = false;
		error_exit_msg("Invalid map");
	}
	ft_free_grid(grid_copy);
	return (is_valid);
}

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
			{
				error_errno("ft_copy_grid");
				return (ft_free_grid(temp_grid), NULL);
			}
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
	if ( x < 0 || x >= map->map_width)
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


