#include "cub3d.h"

char *copy_line(char *src, size_t width)
{
	char	*dest;
	size_t	i;

	dest = malloc(sizeof(char) * (width + 1));
	if (!dest)
		{
		print_error_marker();
    	perror("copy_line");
		return (NULL);
		}
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
		{
		print_error_marker();
    	perror("copy_grid");
		return (NULL);
		}
	i = 0;
	while (i < map->map_height + 1)
		grid_copy[i++] = NULL;
	i = 0;
	while (map->grid[i])
	{
		grid_copy[i] = ft_strdup(map->grid[i]);
			if (!grid_copy[i])
			{
				print_error_marker();
    			perror("copy_grid: ft_strdup failed");
				return (NULL);
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