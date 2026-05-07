/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:55:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 17:28:44 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

static void	init_ray_step(t_game *game, t_ray *r)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (game->player.x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - game->player.x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (game->player.y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - game->player.y) * r->deltadisty;
	}
}

static void	init_ray(t_game *game, t_ray *r)
{
	r->camerax = 2 * r->x / (double)1920 - 1;
	r->raydirx = game->player.dir_x + game->player.plane_x * r->camerax;
	r->raydiry = game->player.dir_y + game->player.plane_y * r->camerax;
	r->mapx = (int)game->player.x;
	r->mapy = (int)game->player.y;
	if (r->raydirx == 0)
		r->deltadistx = 1e30;
	else
		r->deltadistx = fabs(1 / r->raydirx);
	if (r->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1 / r->raydiry);
	r->hit = 0;
	init_ray_step(game, r);
}

static void	perform_dda(t_game *game, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (game->map[r->mapy][r->mapx] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	else
		r->perpwalldist = (r->sidedisty - r->deltadisty);
}

int	raycasting(t_game *game)
{
	t_ray	r;

	r.x = 0;
	while (r.x < 1920)
	{
		init_ray(game, &r);
		perform_dda(game, &r);
		calc_line(game, &r);
		draw_column(game, &r);
		r.x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->screen.img, 0, 0);
	return (1);
}
