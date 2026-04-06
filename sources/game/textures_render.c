/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:17:42 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:24:54 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex	*select_wall_texture(t_game *game, t_ray *ray);
static double	get_wall_x(t_game *game, t_ray *ray);

void	draw_textured_wall(t_game *game, int x, t_ray *ray)
{
	t_tex	*tex;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		y;

	tex = select_wall_texture(game, ray);
	tex_x = (int)(get_wall_x(game, ray) * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) 
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_pixel(&game->frame, x, y, 
			get_texture_pixel(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		y++;
	}
}

static t_tex	*select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->tex_ea);
		return (&game->tex_we);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->tex_so);
		return (&game->tex_no);
	}
}

static double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pl_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pl_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
