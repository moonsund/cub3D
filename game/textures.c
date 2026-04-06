/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 22:42:22 by asharafe          #+#    #+#             */
/*   Updated: 2026/04/04 22:43:08 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture_struct(t_tex *tex);

int	load_textures(t_game *game)
{
	if (load_texture_image(game->mlx, 
			game->map.tex_n, &game->tex_no) != SUCCESS)
		return (FAILURE);
	if (load_texture_image(game->mlx, game->map.tex_s, 
			&game->tex_so) != SUCCESS)
		return (FAILURE);
	if (load_texture_image(game->mlx, game->map.tex_w, 
			&game->tex_we) != SUCCESS)
		return (FAILURE);
	if (load_texture_image(game->mlx, game->map.tex_e, 
			&game->tex_ea) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	load_texture_image(void *mlx, char *path, t_tex *tex)
{
	init_texture_struct(tex);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		error_msg("load_texture_image: mlx_xpm_file_to_image failed\n");
		return (FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, 
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		error_msg("load_texture_image: mlx_get_data_addr failed\n");
		return (FAILURE);
	}
	tex->pixels = (unsigned int *)tex->addr;
	return (SUCCESS);
}

static void	init_texture_struct(t_tex *tex)
{
	tex->img = NULL;
	tex->addr = NULL;
	tex->bpp = 0;
	tex->line_len = 0;
	tex->endian = 0;
	tex->width = 0;
	tex->height = 0;
	tex->pixels = NULL;
}

unsigned int	get_texture_pixel(t_tex *tex, int x, int y)
{
	char	*dst;

	if (!tex || !tex->addr)
		return (0);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}
