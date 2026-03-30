#include "cub3d.h"

int	game_loop(t_game *game)
{
	if (init_graphics(game) != SUCCESS)
		return (FAILURE);
	if (create_game_window(game) != SUCCESS)
		return (FAILURE);
	if (init_frame(game) != SUCCESS)
		return (FAILURE);
	if (load_textures(game) != SUCCESS)
		return (FAILURE);
	
	register_hooks(game);
	render_frame(game);

	// main game loop
	mlx_loop_hook(game->mlx, game_render_loop, game);
	mlx_loop(game->mlx);	
	
	return (SUCCESS);
}