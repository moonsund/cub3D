/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:43:42 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/06 18:26:52 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	has_cub_extension(char *filename);

int	validate_arguments(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (error_msg("Usage: ./cub3d <map_file>."));
	if (!has_cub_extension(argv[1]))
		return (error_msg("validate_arguments: invalid file extension."));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error_errno("validate_arguments."));
	close(fd);
	return (0);
}

static bool	has_cub_extension(char *filename)
{
	int	filename_len;

	filename_len = ft_strlen(filename);
	if (filename_len < 5)
		return (false);
	if (ft_strncmp(&filename[filename_len - 4], ".cub", 4) != 0)
		return (false);
	return (true);
}
