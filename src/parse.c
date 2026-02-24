#include "cub3d.h"

static int	read_file(const char *file_path, t_map *map);
int procces_data_read(t_map *map);
int get_textures_data(t_map *map, char *str);
int get_colours_data(t_map *map, char *str);
static int get_map_data(t_map *map, int i);
static int parse_colours(char *line);

int initialize_map(const char *file_path, t_map *map)
{
	if (count_lines_in_file(file_path, &map->lines_count))
		return (1);

	map->file_data = malloc(sizeof(char *) * (map->lines_count + 1));
	if (!map->file_data)
		return (error_errno("initialize_map"));

	if (!read_file(file_path, map))
		return (1);

	if (!procces_data_read(map))
		return (1);

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
		return (error_errno("read_file"));

	i = 0;
	while (i < map->lines_count)
	{
		line = get_next_line(fd);
		map->file_data[i] = trim_if_needed(line);
		free(line);
		if (!map->file_data[i])
			return (close(fd), free_file_data(map->file_data, i),
				error_errno("read_file"));
		i++;
	}
	map->file_data[i] = NULL;
	close(fd);	
	return (0);
}

int procces_data_read(t_map *map)
{
	size_t i;
	int param_check_flag;

	param_check_flag = 0;
	i = 0;
	while (map->file_data[i] != NULL)
	{
		if ((ft_strncmp(map->file_data[i], "NO", 2) || ft_strncmp(map->file_data[i], "SO", 2)
		|| ft_strncmp(map->file_data[i], "WE", 2) || ft_strncmp(map->file_data[i], "EA", 2)) && get_textures_data(map, map->file_data[i]))
			param_check_flag++;
		
		else if ((ft_strncmp(map->file_data[i], "F", 1) 
		|| ft_strncmp(map->file_data[i], "C", 1)) 
		&& get_colours_data(map, map->file_data[i]))
			param_check_flag++;
		if (param_check_flag == 6)
			break;
		
	}

	get_map_data(map, i);
	return (0);
}	


static int get_map_data(t_map *map, int i)
{
	(void)map;
	(void)i;

	return (0);

}


int get_textures_data(t_map *map, char *str)
{
	(void)map;
	(void)str;
	return (0);
}

int get_colours_data(t_map *map, char *str)
{
	(void)map;
	(void)str;
	parse_colours(str);

	return (0);
}


static int parse_colours(char *line)
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