/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:29:04 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 17:29:32 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_line(t_game *game, t_ray *r)
{
	r->lineheight = (int)(1080 / r->perpwalldist);
	r->drawstart = (r->lineheight * -1) / 2 + 1080 / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + 1080 / 2;
	if (r->drawend >= 1080)
		r->drawend = 1080 - 1;
	if (r->side == 0)
		r->wallx = game->player.y + r->perpwalldist * r->raydiry;
	else
		r->wallx = game->player.x + r->perpwalldist * r->raydirx;
	r->wallx -= floor(r->wallx);
	r->texx = (int)(r->wallx * 64);
	if (r->side == 0 && r->raydirx > 0)
		r->texx = 64 - r->texx - 1;
	if (r->side == 1 && r->raydiry < 0)
		r->texx = 64 - r->texx - 1;
	r->step = 1.0 * 64 / r->lineheight;
	r->texpos = (r->drawstart - 1080 / 2.0 + r->lineheight / 2.0) * r->step;
}

static void	draw_wall(t_game *game, t_ray *r)
{
	while (r->y <= r->drawend)
	{
		r->texy = (int)r->texpos;
		if (r->texy < 0)
			r->texy = 0;
		else if (r->texy >= 64)
			r->texy = 63;
		r->texpos += r->step;
		if (r->side == 0 && r->raydirx > 0)
			r->color = get_tex_color(&game->tex_e, r->texx, r->texy);
		else if (r->side == 0 && r->raydirx < 0)
			r->color = get_tex_color(&game->tex_w, r->texx, r->texy);
		else if (r->side == 1 && r->raydiry > 0)
			r->color = get_tex_color(&game->tex_s, r->texx, r->texy);
		else
			r->color = get_tex_color(&game->tex_n, r->texx, r->texy);
		my_mlx_pixel_put(game, r->x, r->y, r->color);
		r->y++;
	}
}

void	draw_column(t_game *game, t_ray *r)
{
	r->y = 0;
	while (r->y < r->drawstart)
	{
		my_mlx_pixel_put(game, r->x, r->y, game->ceiling_color);
		r->y++;
	}
	draw_wall(game, r);
	while (r->y < 1080)
	{
		my_mlx_pixel_put(game, r->x, r->y, game->ground_color);
		r->y++;
	}
}
