#include "cub3d.h"

void print_file_data(t_map *map)
{
    size_t i = 0;
    while (i < map->lines_count)
    {
        printf("#%zu: %s\n", i, map->file_data[i]);
        i++;
    }
}

void	debug_dump_parsed(const t_map *map)
{
	printf("NO=%s\n", map->tex_N);
	printf("SO=%s\n", map->tex_S);
	printf("WE=%s\n", map->tex_W);
	printf("EA=%s\n", map->tex_E);
	// printf("F=%d,%d,%d\n", map->floor_color.r, map->floor_color.g, map->floor_color.b);
	// printf("C=%d,%d,%d\n", map->ceiling_color.r, map->ceiling_color.g, map->ceiling_color.b);
	printf("PLAYER=%zu,%zu,%c\n", map->player_x, map->player_y, map->player_dir);
	printf("MAP_W=%zu\n", map->map_width);
	printf("MAP_H=%zu\n", map->map_height);
	printf("MAP:\n");
	print_map_grid((const char **)map->grid, map->map_height, map->map_width);
}

void	print_map_grid(const char **grid, size_t h, size_t w)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			putchar(grid[y][x]);
			x++;
		}
		putchar('\n');
		y++;
	}
}