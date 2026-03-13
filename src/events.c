#include "cub3d.h"

void	register_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_key_hook(game->win, handle_keys, game);
}

static int	handle_keys(int keycode, t_game *game)
{
	bool	need_redraw;

	need_redraw = false;
	// if (keycode == XK_Up)
	// 	change_zoom(fdf, +1, &need_redraw);
	// else if (keycode == XK_Down)
	// 	change_zoom(fdf, -1, &need_redraw);
	// else if (keycode == XK_Right)
	// 	change_z_scale(fdf, +1, &need_redraw);
	// else if (keycode == XK_Left)
	// 	change_z_scale(fdf, -1, &need_redraw);
	// else if (keycode == XK_Escape)
	// 	handle_close(fdf);
	// else if (keycode == XK_s)
	// 	switch_projection(fdf, &need_redraw);
	// if (need_redraw)
	// 	redraw(fdf);
	return (0);
}

static int	handle_close(t_game *game)
{
	cleanup(game);
	exit(0);
}