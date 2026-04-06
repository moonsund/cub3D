/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:29:20 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:30:24 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_file_data(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->lines_count)
	{
		printf("#%u: %s\n", i, map->file_data[i]);
		i++;
	}
}

void	debug_dump_parsed(const t_game *game)
{
	t_map	map;

	map = game->map;
	printf("NO=%s\n", map.tex_n);
	printf("SO=%s\n", map.tex_s);
	printf("WE=%s\n", map.tex_w);
	printf("EA=%s\n", map.tex_e);
	printf("F=%d\n", map.floor_color);
	printf("C=%d\n", map.ceiling_color);
	printf("PLAYER=%d,%d,%c\n", (int)game->player.pl_x, (int)game->player.pl_y,
		game->player.pl_dir);
	printf("MAP_W=%u\n", map.map_width);
	printf("MAP_H=%u\n", map.map_height);
	printf("MAP:\n");
	print_map_grid((const char **)map.grid, map.map_height, map.map_width);
}

void	print_map_grid(const char **grid, size_t height, size_t width)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < height)
	{
		printf("grid[%zu]=", y);
		putchar('"');
		x = 0;
		while (x < width)
		{
			putchar(grid[y][x]);
			x++;
		}
		putchar('"');
		putchar('\n');
		y++;
	}
}
