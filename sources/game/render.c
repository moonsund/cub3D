/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:23:43 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:42:07 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	game_render_loop(t_game *game)
{
	update_player(game);
	render_frame(game);
	return (SUCCESS);
}

bool	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.map_width || y >= game->map.map_height)
		return (true);
	if (game->map.grid[y][x] == '1')
		return (true);
	if (game->map.grid[y][x] == ' ')
		return (true);
	return (false);
}
