/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:32:55 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/04/06 18:25:38 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_data_read(t_map *map, t_player *player)
{
	size_t	i;
	int		params;
	char	*line;

	i = 0;
	params = 0;
	while (map->file_data[i] && params < 6)
	{
		line = map->file_data[i];
		if (line[0] == '\n' || line[0] == '\0')
		{
			i++;
			continue ;
		}
		if (parse_map_params_lines(map, line, &params) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (params < 6)
		return (error_msg("procces_data_read: missing data."));
	if (parse_map_section(map, player, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_map_params_lines(t_map *map, char *line, int *params)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if (parse_texture_line(map, line) == FAILURE)
			return (FAILURE);
		(*params)++;
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		if (parse_colour_line(map, line) == FAILURE)
			return (FAILURE);
		(*params)++;
	}
	else
		return (error_msg("procces_data_read: data corrupted."));
	return (SUCCESS);
}

int	parse_texture_line(t_map *map, char *str)
{
	char	**tmp;
	int		return_code;

	tmp = ft_split(str, ' ');
	if (!tmp)
		return (error_errno("parse_texture_line: split."));
	if (!tmp[0] || !tmp[1] || tmp[2])
	{
		free_split(tmp);
		return (error_msg("parse_texture_line: invalid texture line format."));
	}
	return_code = 0;
	if (ft_strncmp(tmp[0], "NO", 3) == 0)
		return_code = set_texture(&map->tex_n, tmp[1]);
	else if (ft_strncmp(tmp[0], "SO", 3) == 0)
		return_code = set_texture(&map->tex_s, tmp[1]);
	else if (ft_strncmp(tmp[0], "EA", 3) == 0)
		return_code = set_texture(&map->tex_e, tmp[1]);
	else if (ft_strncmp(tmp[0], "WE", 3) == 0)
		return_code = set_texture(&map->tex_w, tmp[1]);
	else
		return_code = error_msg("parse_texture_line: unknown texture id.");
	free_split(tmp);
	return (return_code);
}

int	parse_colour_line(t_map *map, char *str)
{
	char	**tmp;
	int		return_code;

	tmp = ft_split(str, ' ');
	if (!tmp)
		return (error_errno("get_colours_data: split."));
	if (!tmp[0] || !tmp[1] || tmp[2])
	{
		free_split(tmp);
		return (error_msg("get_colours_data: invalid colour line format."));
	}
	return_code = 0;
	if (tmp[0][0] == 'F' && tmp[0][1] == '\0')
		return_code = set_colour(tmp[1], &map->floor_color);
	else if (tmp[0][0] == 'C' && tmp[0][1] == '\0')
		return_code = set_colour(tmp[1], &map->ceiling_color);
	else
		return_code = error_msg("get_colours_data: unknown colour id".);
	free_split(tmp);
	return (return_code);
}
