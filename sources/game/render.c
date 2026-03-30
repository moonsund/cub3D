#include "cub3d.h"

void	render_frame(t_game *game)
{
	draw_background(game);
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel(&game->frame, x, y, game->map.ceiling_color);
			else
				put_pixel(&game->frame, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
// {
// 	int	y;

// 	if (start < 0)
// 		start = 0;
// 	if (end >= WIN_HEIGHT)
// 		end = WIN_HEIGHT - 1;
// 	y = start;
// 	while (y <= end)
// 	{
// 		put_pixel(&game->frame, x, y, color);
// 		y++;
// 	}
// }

int	game_render_loop(t_game *game)
{
	update_player(game);
	render_frame(game);
	return (0);
}