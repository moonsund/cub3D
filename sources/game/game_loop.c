/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:30:59 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:31:18 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	if (init_graphics(game) != SUCCESS)
		return (FAILURE);
	if (create_game_window(game) != SUCCESS)
		return (FAILURE);
	if (init_frame(game) != SUCCESS)
		return (FAILURE);
	if (load_textures(game) != SUCCESS)
		return (FAILURE);
	register_hooks(game);
	render_frame(game);
	mlx_loop_hook(game->mlx, game_render_loop, game);
	mlx_loop(game->mlx);
	return (SUCCESS);
}
