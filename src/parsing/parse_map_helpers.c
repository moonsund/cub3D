#include "cub3d.h"


void skip_empty_lines(char **lines, int *i)
{
    while (lines[*i])
    {
        if (line_is_empty(lines[*i]))
            (*i)++;
        else
            break;
    }
}

bool line_is_empty(char *line)
{
    size_t i = 0;

    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n')
            return (false);
        i++;
    }
    return (true);
}

void get_map_dimensions(char **lines, size_t *height, size_t *width, int i)
{
    size_t line_len;

    *height = 0;
    *width = 0;
    while (lines[i])
    {
        if (line_is_empty(lines[i]))
            break;
        line_len = ft_strlen(lines[i]);
        if (line_len > *width)
            *width = line_len;
        (*height)++;
        i++;
    }
}

int check_trailing_content(char **lines, int i)
{
    while (lines[i])
    {
        if (!line_is_empty(lines[i]))
            return (error_msg("check_trailing_content: unexpected content after map"));
        i++;
    }
    return (SUCCESS);
}

int	validate_map_chars(char **lines, int i)
{
	int	j;

	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!(lines[i][j] == 'N' || lines[i][j] == 'S'
				|| lines[i][j] == 'E' || lines[i][j] == 'W'
				|| lines[i][j] == '0' || lines[i][j] == '1'
				|| lines[i][j] == ' ' || lines[i][j] == '\n'))
				return (error_msg("validate_map_chars: map contains forbidden character"));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

char *copy_line(char *src, size_t width)
{
	char	*dest;
	size_t	i;

	dest = malloc(sizeof(char) * (width + 1));
	if (!dest)
		return (error_errno("copy_line"));
	i = 0;
	while (i < width && src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < width)
		dest[i++] = ' ';
	dest[i] = '\0';
	return (dest);
}

char **copy_grid(t_map *map)
{
	char	**grid_copy;
	int		i;

	grid_copy = malloc(sizeof(char *) * (map->map_height + 1));
	if (!grid_copy)
		return (error_errno("copy_grid"));
	i = 0;
	while (i < map->map_height + 1)
		grid_copy[i++] = NULL;
	i = 0;
	while (map->grid[i])
	{
		grid_copy[i] = ft_strdup(map->grid[i]);
			if (!grid_copy[i])
			{
				free_grid(grid_copy);
				return (error_errno("copy_grid: ft_strdup failed"));
			}
		i++;
	}
	grid_copy[i] = NULL;
	return (grid_copy);
}

void	set_player_position(t_player *player, char dir, int y, int x)
{
	player->pl_dir = dir;
	player->pl_y = y;
    player->pl_x = x;
}