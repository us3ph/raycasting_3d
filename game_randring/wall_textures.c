/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanflous <yanflous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:58:00 by yanflous          #+#    #+#             */
/*   Updated: 2025/07/28 13:27:52 by yanflous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_image	*get_img_ptr(t_game *game, t_intercept_hit obj_hit)
{
	t_textures	*textures;

	textures = &game->textures;
	if (obj_hit.inter_dir == North)
		return (&textures->t_north);
	else if (obj_hit.inter_dir == South)
		return (&textures->t_south);
	else if (obj_hit.inter_dir == East)
		return (&textures->t_east);
	return (&textures->t_west);
}

double	get_hit_pos(t_game *game, t_intercept_hit obj_hit)
{
	double	hit_pos;

	if (game->cast_data.horizontal_hit)
		hit_pos = fmod(obj_hit.intercept.x, TILE_SIZE);
	else
		hit_pos = fmod(obj_hit.intercept.y, TILE_SIZE);
	return (hit_pos);
}

double	get_texture_y_offset(int wall_height, double step)
{
	int		wall_top_clipped;
	double	tex_pos;

	tex_pos = 0;
	wall_top_clipped = (SCREEN_HEIGHT / 2) - (wall_height / 2);
	if (wall_top_clipped < 0)
		tex_pos = (-wall_top_clipped) * step;
	else
		tex_pos = 0;
	return (tex_pos);
}

// Y -> row
// X -> column

void	set_wall_textures(t_game *game, int x, int top, int bottom)
{
	t_image		*img;
	int			y;
	double		step;
	double		hit_pos;
	double		tex_pos;

	y = top;
	img = get_img_ptr(game, game->cast_data.obj_hit);
	step = (double)img->height / game->cast_data.wall_height;
	tex_pos = get_texture_y_offset(game->cast_data.wall_height, step);
	hit_pos = get_hit_pos(game, game->cast_data.obj_hit);
	game->cast_data.tex_offset_x = (int)((hit_pos / TILE_SIZE) * img->width);
	while (y < bottom)
	{
		game->cast_data.tex_offset_y = (int)tex_pos % img->height;
		game->cast_data.color = *(int *)(img->addr
				+ game->cast_data.tex_offset_y * img->size_line
				+ game->cast_data.tex_offset_x * (img->bpp / 8));
		my_mlx_pixel_put(game, x, y, game->cast_data.color);
		tex_pos += step;
		y++;
	}
}
