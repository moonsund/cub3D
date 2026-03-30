#include "cub3d.h"

void	register_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
}

int	close_game(t_game *game)
{
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	return (SUCCESS);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_game(game);
	else if (keycode == KEY_W)
		game->key_w = 1;
	else if (keycode == KEY_S)
		game->key_s = 1;
	else if (keycode == KEY_A)
		game->key_a = 1;
	else if (keycode == KEY_D)
		game->key_d = 1;
	else if (keycode == LEFT_ARROW)
		game->key_left = 1;
	else if (keycode == RIGHT_ARROW)
		game->key_right = 1;
	return (SUCCESS);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_w = 0;
	else if (keycode == KEY_S)
		game->key_s = 0;
	else if (keycode == KEY_A)
		game->key_a = 0;
	else if (keycode == KEY_D)
		game->key_d = 0;
	else if (keycode == LEFT_ARROW)
		game->key_left = 0;
	else if (keycode == RIGHT_ARROW)
		game->key_right = 0;
	return (SUCCESS);
}