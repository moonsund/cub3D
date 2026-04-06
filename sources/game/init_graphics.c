/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:31:27 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/06 18:27:10 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		error_msg("init_graphics: mlx_init failed.");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	create_game_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game->win)
	{
		error_msg("create_game_window: wint_init failed.");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_frame(t_game *game)
{
	game->frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img)
	{
		error_msg("init_frame: image_init failed.");
		return (FAILURE);
	}
	game->frame.addr = mlx_get_data_addr(game->frame.img,
			&game->frame.bpp,
			&game->frame.line_len,
			&game->frame.endian);
	if (!game->frame.addr)
	{
		error_msg("init_frame: addr_init failed.");
		return (FAILURE);
	}
	return (SUCCESS);
}
