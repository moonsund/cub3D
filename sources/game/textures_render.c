#include "cub3d.h"
#include <math.h>

t_tex	*select_wall_texture(t_game *game, int side,
	double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (&game->tex_we);
		else
			return (&game->tex_ea);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&game->tex_no);
		else
			return (&game->tex_so);
	}
}

static double	get_wall_x(t_game *game, int side,
	double ray_dir_x, double ray_dir_y, double perp_wall_dist)
{
	double	wall_x;

	if (side == 0)
		wall_x = game->player.pl_y + perp_wall_dist * ray_dir_y;
	else
		wall_x = game->player.pl_x + perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	draw_textured_wall(t_game *game, int x, int draw_start,
	int draw_end, int side, double ray_dir_x,
	double ray_dir_y, double perp_wall_dist)
{
	t_tex			*tex;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	unsigned int	color;
	int				y;

	tex = select_wall_texture(game, side, ray_dir_x, ray_dir_y);
	wall_x = get_wall_x(game, side, ray_dir_x, ray_dir_y, perp_wall_dist);
	tex_x = (int)(wall_x * (double)tex->width);

	if (side == 0 && ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (side == 1 && ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;

	step = 1.0 * tex->height / (draw_end - draw_start);
	tex_pos = (draw_start - WIN_HEIGHT / 2
			+ (draw_end - draw_start) / 2) * step;

	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(&game->frame, x, y, color);
		y++;
	}
}