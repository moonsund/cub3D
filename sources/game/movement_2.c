/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:33:38 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:35:06 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_walkable(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0
		|| map_x >= game->map.map_width
		|| map_y >= game->map.map_height)
		return (false);
	if (game->map.grid[map_y][map_x] == '1')
		return (false);
	if (game->map.grid[map_y][map_x] == ' ')
		return (false);
	return (true);
}

void	move_forward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x + game->player.dir_x * move_speed;
	new_y = game->player.pl_y + game->player.dir_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	move_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x - game->player.dir_x * move_speed;
	new_y = game->player.pl_y - game->player.dir_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	move_left(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x - game->player.plane_x * move_speed;
	new_y = game->player.pl_y - game->player.plane_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	move_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x + game->player.plane_x * move_speed;
	new_y = game->player.pl_y + game->player.plane_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}
