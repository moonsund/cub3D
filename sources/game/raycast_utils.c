#include "cub3d.h"

int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.map_width || y >= game->map.map_height)
		return (1);
	if (game->map.grid[y][x] == '1')
		return (1);
	if (game->map.grid[y][x] == ' ')
		return (1);
	return (0);
}