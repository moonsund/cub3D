/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:33:11 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/03/28 13:56:06 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines_in_file(const char *file_path, int *lines_count)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (error_errno("count_lines"));
	line = get_next_line(fd);
	if (!line)
		return (close(fd), error_msg("count_lines: The file is empty.\n"));
	i = 0;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	*lines_count = i;
	close(fd);
	return (0);
}

int	read_file(const char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

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

char	*trim_if_needed(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E'
		|| str[i] == 'F' || str[i] == 'C')
		return (ft_strtrim(str, " \n\t"));
	return (ft_strdup(str));
}

void	free_file_data(char **file_data, int i) //TO_DO
{
	(void)file_data;
	(void)i;
}
