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
	printf("F=%d\n", map->floor_color);
	printf("C=%d\n", map->ceiling_color);
	printf("PLAYER=%zu,%zu,%c\n", map->player_x, map->player_y, map->player_dir);
	printf("MAP_W=%zu\n", map->map_width);
	printf("MAP_H=%zu\n", map->map_height);
	printf("MAP:\n");
	print_map_grid((const char **)map->grid, map->map_height, map->map_width);
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