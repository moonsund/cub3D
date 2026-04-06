/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:33:32 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/04/06 18:25:55 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map_chars(char **lines, int i)
{
	int		j;
	char	*err_msg;

	err_msg = "validate_map_chars: map contains forbidden character.";
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!(lines[i][j] == 'N' || lines[i][j] == 'S'
				|| lines[i][j] == 'E' || lines[i][j] == 'W'
				|| lines[i][j] == '0' || lines[i][j] == '1'
				|| lines[i][j] == ' ' || lines[i][j] == '\n'))
				return (error_msg(err_msg), FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
