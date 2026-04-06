/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:35:26 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:39:26 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dir(t_player *player, double x, double y);
static void	init_plane(t_player *player, double px, double py);

void	init_player_direction(t_player *player)
{
	if (player->pl_dir == 'N')
	{
		init_dir(player, 0.0, -1.0);
		init_plane(player, 0.66, 0.0);
	}
	else if (player->pl_dir == 'S')
	{
		init_dir(player, 0.0, 1.0);
		init_plane(player, -0.66, 0.0);
	}
	else if (player->pl_dir == 'E')
	{
		init_dir(player, 1.0, 0.0);
		init_plane(player, 0.0, 0.66);
	}
	else if (player->pl_dir == 'W')
	{
		init_dir(player, -1.0, 0.0);
		init_plane(player, 0.0, -0.66);
	}
}

static void	init_dir(t_player *player, double x, double y)
{
	player->dir_x = x;
	player->dir_y = y;
}

static void	init_plane(t_player *player, double px, double py)
{
	player->plane_x = px;
	player->plane_y = py;
}
