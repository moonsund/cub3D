/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:28:10 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:29:12 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	initialize_game(&game);
	if (validate_arguments(argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (parse_game_config(argv[1], &game.map, &game.player) == FAILURE)
		return (cleanup_map(&game.map), EXIT_FAILURE);
	debug_dump_parsed(&game);
	cleanup_map(&game.map);
	return (0);
}
