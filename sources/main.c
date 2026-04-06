/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:27:54 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:28:56 by asharafe         ###   ########.fr       */
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
		return (cleanup_game(&game), EXIT_FAILURE);
	init_player_direction(&game.player);
	if (game_loop(&game) == FAILURE)
		return (cleanup_game(&game), EXIT_FAILURE);
	cleanup_game(&game);
	return (0);
}
