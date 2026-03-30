#include "cub3d.h"

static void	draw_square(t_game *game, int start_x, int start_y, int color);
static void	draw_player_marker(t_game *game);
static void	draw_player_direction(t_game *game);

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		while (x < game->map.map_width)
		{
			if (game->map.grid[y][x] == '1')
				color = 0x888888;
			else if (game->map.grid[y][x] == ' ')
				color = 0x000000;
			else
				color = 0x222222;
			draw_square(game,
				MINIMAP_OFFSET_X + x * MINIMAP_TILE,
				MINIMAP_OFFSET_Y + y * MINIMAP_TILE,
				color);
			x++;
		}
		y++;
	}
	draw_player_marker(game);
	draw_player_direction(game);
}

static void	draw_square(t_game *game, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_TILE)
	{
		x = 0;
		while (x < MINIMAP_TILE)
		{
			put_pixel(&game->frame, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_player_marker(t_game *game)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	center_x = MINIMAP_OFFSET_X + (int)(game->player.pl_x * MINIMAP_TILE);
	center_y = MINIMAP_OFFSET_Y + (int)(game->player.pl_y * MINIMAP_TILE);
	y = -PLAYER_SIZE;
	while (y <= PLAYER_SIZE)
	{
		x = -PLAYER_SIZE;
		while (x <= PLAYER_SIZE)
		{
			put_pixel(&game->frame, center_x + x, center_y + y, 0xFF0000);
			x++;
		}
		y++;
	}
}

static void	draw_player_direction(t_game *game)
{
	int		i;
	int		x;
	int		y;
	double	step;

	i = 0;
	step = 0.5;
	while (i < DIR_LINE_LEN * 2)
	{
		x = MINIMAP_OFFSET_X
			+ (int)((game->player.pl_x + game->player.dir_x * i * step / MINIMAP_TILE)
				* MINIMAP_TILE);
		y = MINIMAP_OFFSET_Y
			+ (int)((game->player.pl_y + game->player.dir_y * i * step / MINIMAP_TILE)
				* MINIMAP_TILE);
		put_pixel(&game->frame, x, y, 0xFF0000);
		i++;
	}
}

