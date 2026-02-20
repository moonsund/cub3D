#include "cub3d.h"

static int	read_file(const char *file_path, t_map *map);
int get_textures_data(t_map *map, t_list curr);

int initialize_map(const char *file_path, t_map *map)
{
	if (count_lines_in_file(file_path, &map->lines_count))
		return (1);

	map->file_data = malloc(sizeof(char *) * (map->lines_count + 1));
	if (!map->file_data)
		return (print_error("initialize_map: malloc file data.\n"));

	if (!read_file(file_path, map))
		return (1);

	// if (!procces_data(map));
	// 	return (1);

	// if (!parce_data(map));
	// 	return (1);

	// if (!validate_data(map));
	// 	return (1);
	return (0);
}

static int	read_file(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	size_t i;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (print_error("read_file: Could not open the file.\n"));

	i = 0;
	while (i < map->lines_count)
	{
		line = get_next_line(fd);
		map->file_data[i] = trim_if_needed(line);
		free(line);
		if (!map->file_data[i])
			return (close(fd), free_file_data(map->file_data, i),
				print_error("read_file: malloc dup or trim failed.\n"));
		i++;
	}
	map->file_data[i] = NULL;
	close(fd);	
	return (0);
}
/*
int procces_data_read(t_map *map)
{
	size_t i;
	int param_check_flag;

	i = 0;
	while (i)
	{
		if (ft_strncmp(curr->content, "NO", 2) || ft_strncmp(curr->content, "SO", 2)
		|| ft_strncmp(curr->content, "WE", 2) || ft_strncmp(curr->content, "EA", 2) && get_textures_data(map, curr))
			param_check_flag++;
		
		else if (ft_strncmp(curr->content, "F", 1) || ft_strncmp(curr->content, "C", 1) && get_colours_data(map, curr))
			param_check_flag++;
		
		
	}

	get_map_data(map);
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

int get_textures_data(t_map *map, t_list curr)
{



}

*/