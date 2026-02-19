#include "cub3d.h"

static int	read_file(const char *file_path, t_map *map);
// int get_textures_data(t_map *map, t_list curr);

int initialize_map(const char *file_path, t_map *map)
{
	if (count_lines_in_file(file_path, &map->lines_count))
		return (1);

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
	char	*tmp;
	int i;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (print_error("read_file: Could not open the file.\n"));

	line = get_next_line(fd);
	if (!line)
		return (close(fd), print_error("map file is empty.\n"));

	i = 0;
	while (i <= map->lines_count)
	{
		line = get_next_line(fd);
		tmp = ft_strtrim(line, " \n\t");
		free(line);
		if (!tmp)
			return (close(fd), free_file_data(map->file_data, i),
				print_error("normalize failed.\n"));
		map->file_data[i] = ft_strdup(tmp);
		if (!map->file_data[i])
			return (close(fd), free_file_data(map->file_data, i),
				print_error("string duplication failed.\n"));
		i++;
	}
	close(fd);
	return (0);
}

/*

int procces_data_read(t_map *map)
{
	t_list *curr;
	int param_check_flag;

	curr = map->file_data;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->content, "NO", 2) || ft_strncmp(curr->content, "SO", 2)
		|| ft_strncmp(curr->content, "WE", 2) || ft_strncmp(curr->content, "EA", 2) && get_textures_data(map, curr))
			param_check_flag++;
		
		else if (ft_strncmp(curr->content, "F", 1) || ft_strncmp(curr->content, "C", 1) && get_colours_data(map, curr))
			param_check_flag++;
		
		
		curr = curr->next;
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