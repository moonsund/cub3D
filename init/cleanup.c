/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:06:30 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:20:30 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_textures(t_game *game);

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_map(&game->map);
	cleanup_textures(game);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	get_next_line(-1);
}

void	cleanup_map(t_map *map)
{
	int	i;

	if (map->file_data)
	{
		i = 0;
		while (i < map->lines_count)
			free(map->file_data[i++]);
		free(map->file_data);
		map->file_data = NULL;
	}
	free(map->tex_n);
	map->tex_n = NULL;
	free(map->tex_e);
	map->tex_e = NULL;
	free(map->tex_s);
	map->tex_s = NULL;
	free(map->tex_w);
	map->tex_w = NULL;
	if (map->grid)
		free_grid(map->grid);
}

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	cleanup_textures(t_game *game)
{
	if (game->tex_no.img)
		mlx_destroy_image(game->mlx, game->tex_no.img);
	if (game->tex_so.img)
		mlx_destroy_image(game->mlx, game->tex_so.img);
	if (game->tex_we.img)
		mlx_destroy_image(game->mlx, game->tex_we.img);
	if (game->tex_ea.img)
		mlx_destroy_image(game->mlx, game->tex_ea.img);
}
