/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:33:27 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/04/06 18:25:52 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_empty_lines(char **lines, int *i)
{
	while (lines[*i])
	{
		if (line_is_empty(lines[*i]))
			(*i)++;
		else
			break ;
	}
}

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

void	get_map_dimensions(char **lines, int *height, int *width, int i)
{
	int	line_len;

	*height = 0;
	*width = 0;
	while (lines[i])
	{
		if (line_is_empty(lines[i]))
			break ;
		line_len = ft_map_line_length(lines[i]);
		if (line_len > *width)
			*width = line_len;
		(*height)++;
		i++;
	}
}

int	ft_map_line_length(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

int	check_trailing_content(char **lines, int i)
{
	char	*err_msg;

	err_msg = "check_trailing_content: unexpected content after map.";
	while (lines[i])
	{
		if (!line_is_empty(lines[i]))
			return (error_msg(err_msg));
		i++;
	}
	return (SUCCESS);
}
