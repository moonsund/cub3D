#include "cub3d.h"

int initialize_map(const char *file_path, t_map *map)
{
	if (!read_file(file_path, map))
		return (1);

	if (!procces_data(map));
		return (1);

	if (!parce_data(map));
		return (1);

	if (!validate_data(map));
		return (1);


}

int	read_file(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	char	*tmp;
	t_list	*node;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (print_error("The file is not opened.\n"));

	line = get_next_line(fd);
	if (!line)
		return (close(fd), print_error("map file is empty.\n"));

	while (line)
	{
		tmp = normilize(line);
		free(line);
		if (!tmp)
			return (close(fd), free_lst(map->map_data), map->map_data = NULL,
				print_error("normalize failed.\n"));

		node = ft_lstnew(tmp);
		if (!node)
			return (free(tmp), close(fd), free_lst(map->map_data),
				map->map_data = NULL, print_error("malloc failed.\n"));

		ft_lstadd_back(&map->map_data, node);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}


int procces_data_read(map)
{
	while ()
	{
		get_colours_data()
		
		get_textures_data()
	}

	get_map_data()
}	


static int parse_map(line)
{
	(void)line;

	return (0);

}

static int parse_colours(line)
{
	(void)line;
	// int color = (r << 16) | (g << 8) | b;

	// распарсить строку
	// проверить:
	// 3 числа
	// только цифры
	// диапазон 0–255
	// сохранить как int color
	return (0);

}

static int parse_walls(line)
{
	(void)line;
	return (0);

}