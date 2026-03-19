#include "cub3d.h"

static int	handle_close(t_game *game);
static int	handle_keys(int keycode, t_game *game);

void	register_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_key_hook(game->win, handle_keys, game);
}

static int	handle_keys(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	
	return (0);
}

static int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
}