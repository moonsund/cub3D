#include "cub3d.h"
#include <math.h>

static int	is_walkable(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0
		|| map_x >= game->map.map_width
		|| map_y >= game->map.map_height)
		return (0);
	if (game->map.grid[map_y][map_x] == '1')
		return (0);
	if (game->map.grid[map_y][map_x] == ' ')
		return (0);
	return (1);
}

void	move_forward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x + game->player.dir_x * move_speed;
	new_y = game->player.pl_y + game->player.dir_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	move_backward(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x - game->player.dir_x * move_speed;
	new_y = game->player.pl_y - game->player.dir_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	move_left(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x - game->player.plane_x * move_speed;
	new_y = game->player.pl_y - game->player.plane_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	move_right(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pl_x + game->player.plane_x * move_speed;
	new_y = game->player.pl_y + game->player.plane_y * move_speed;
	if (is_walkable(game, new_x, game->player.pl_y))
		game->player.pl_x = new_x;
	if (is_walkable(game, game->player.pl_x, new_y))
		game->player.pl_y = new_y;
}

void	rotate_left(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed)
		- game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed)
		+ game->player.dir_y * cos(-rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed)
		- game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed)
		+ game->player.plane_y * cos(-rot_speed);
}

void	rotate_right(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}

void	update_player(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.08;
	rot_speed = 0.05;
	if (game->key_w)
		move_forward(game, move_speed);
	if (game->key_s)
		move_backward(game, move_speed);
	if (game->key_a)
		move_left(game, move_speed);
	if (game->key_d)
		move_right(game, move_speed);
	if (game->key_left)
		rotate_left(game, rot_speed);
	if (game->key_right)
		rotate_right(game, rot_speed);
}