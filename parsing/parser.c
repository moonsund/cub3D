/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:33:41 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/03/28 13:56:49 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_game_config(const char *file_path, t_map *map, t_player *player)
{
	if (count_lines_in_file(file_path, &map->lines_count) == FAILURE)
		return (FAILURE);
	map->file_data = malloc(sizeof(char *) * (map->lines_count + 1));
	if (!map->file_data)
		return (error_errno("fill_map"));
	if (read_file(file_path, map) == FAILURE)
		return (FAILURE);
	if (process_data_read(map, player) == FAILURE)
		return (FAILURE);
	return (0);
}
