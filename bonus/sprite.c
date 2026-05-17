/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:54:01 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/17 18:15:49 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_transform(t_game *game, t_sprite_cast *v)
{
	v->spr_x = game->sprite.x - game->player.x;
	v->spr_y = game->sprite.y - game->player.y;
	v->invdet = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	v->trans_x = v->invdet * (game->player.dir_y * v->spr_x - game->player.dir_x
			* v->spr_y);
	v->trans_y = v->invdet * (-game->player.plane_y * v->spr_x
			+ game->player.plane_x * v->spr_y);
}

static void	calc_bounds(t_sprite_cast *v)
{
	v->screen_x = (int)(1920 / 2)*(1 + v->trans_x / v->trans_y);
	v->dim = abs((int)(1080 / v->trans_y));
	v->start_y = -v->dim / 2 + 1080 / 2;
	if (v->start_y < 0)
		v->start_y = 0;
	v->end_y = v->dim / 2 + 1080 / 2;
	if (v->end_y >= 1080)
		v->end_y = 1080 - 1;
	v->start_x = -v->dim / 2 + v->screen_x;
	if (v->start_x < 0)
		v->start_x = 0;
	v->end_x = v->dim / 2 + v->screen_x;
	if (v->end_x > 1920)
		v->end_x = 1920;
}

static void	put_sprite_pixels(t_game *game, t_sprite_cast *v, int stripe,
		int tex_x)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;

	y = v->start_y;
	while (y < v->end_y)
	{
		d = y - 1080 / 2 + v->dim / 2;
		tex_y = (d * 200) / v->dim;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= 200)
			tex_y = 199;
		color = get_tex_color(&game->tex_sprite, tex_x, tex_y);
		if (color != 0)
			my_mlx_pixel_put(game, stripe, y, color);
		y++;
	}
}

static void	draw_stripe(t_game *game, t_sprite_cast *v, int stripe)
{
	int	tex_x;

	tex_x = (stripe - (-v->dim / 2 + v->screen_x)) * 200 / v->dim;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 200)
		tex_x = 199;
	if (v->trans_y < game->z_buffer[stripe] && v->trans_y > 0)
		put_sprite_pixels(game, v, stripe, tex_x);
}

void	render_sprite(t_game *game)
{
	t_sprite_cast	v;
	int				stripe;

	calc_transform(game, &v);
	if (v.trans_y <= 0)
		return ;
	calc_bounds(&v);
	stripe = v.start_x;
	while (stripe < v.end_x)
	{
		draw_stripe(game, &v, stripe);
		stripe++;
	}
}
