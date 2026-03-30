#include "cub3d.h"
#include <math.h>


static int	perform_dda(t_game *game, int *map_x, int *map_y,
		double ray_dir_x, double ray_dir_y, double *perp_wall_dist);
static void	draw_wall_slice(t_game *game, int x, double perp_wall_dist,
	int side, double ray_dir_x, double ray_dir_y);
static void	calc_step_and_side(t_game *game, double ray_dir_x, double ray_dir_y,
		int *step_x, int *step_y, double *side_dist_x, double *side_dist_y);

void	raycast(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	perp_wall_dist;
	int		side;

	x = 0;
	while (x < WIN_WIDTH)
	{
		camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
		ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		map_x = (int)game->player.pl_x;
		map_y = (int)game->player.pl_y;
		side = perform_dda(game, &map_x, &map_y,
				ray_dir_x, ray_dir_y, &perp_wall_dist);
		draw_wall_slice(game, x, perp_wall_dist, side, ray_dir_x, ray_dir_y);
		x++;
	}
}

static int	perform_dda(t_game *game, int *map_x, int *map_y,
		double ray_dir_x, double ray_dir_y, double *perp_wall_dist)
{
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;

	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1.0 / ray_dir_y);
	calc_step_and_side(game, ray_dir_x, ray_dir_y,
		&step_x, &step_y, &side_dist_x, &side_dist_y);
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			*map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			*map_y += step_y;
			side = 1;
		}
		if (is_wall(game, *map_x, *map_y))
			break ;
	}
	if (side == 0)
		*perp_wall_dist = side_dist_x - delta_dist_x;
	else
		*perp_wall_dist = side_dist_y - delta_dist_y;
	return (side);
}

static void	draw_wall_slice(t_game *game, int x, double perp_wall_dist,
	int side, double ray_dir_x, double ray_dir_y)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (perp_wall_dist <= 0.0)
		perp_wall_dist = 0.1;

	line_height = (int)(WIN_HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;

	draw_textured_wall(game, x, draw_start, draw_end,
		side, ray_dir_x, ray_dir_y, perp_wall_dist);
}

static void	calc_step_and_side(t_game *game, double ray_dir_x, double ray_dir_y,
		int *step_x, int *step_y, double *side_dist_x, double *side_dist_y)
{
	double	delta_dist_x;
	double	delta_dist_y;

	if (ray_dir_x == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(1.0 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_dist_x = (game->player.pl_x - (int)game->player.pl_x) * delta_dist_x;
	}
	else
	{
		*step_x = 1;
		*side_dist_x = ((int)game->player.pl_x + 1.0 - game->player.pl_x)
			* delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_dist_y = (game->player.pl_y - (int)game->player.pl_y) * delta_dist_y;
	}
	else
	{
		*step_y = 1;
		*side_dist_y = ((int)game->player.pl_y + 1.0 - game->player.pl_y)
			* delta_dist_y;
	}
}

