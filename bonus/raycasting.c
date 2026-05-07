/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:55:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 17:07:15 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_step(t_game *game, t_raycast *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->player.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->player.y) * r->delta_dist_y;
	}
}

static void	init_ray(t_game *game, t_raycast *r)
{
	r->is_door = 0;
	r->hit = 0;
	r->camera_x = 2 * r->x / (double)1920 - 1;
	r->ray_dir_x = game->player.dir_x + game->player.plane_x * r->camera_x;
	r->ray_dir_y = game->player.dir_y + game->player.plane_y * r->camera_x;
	r->map_x = (int)game->player.x;
	r->map_y = (int)game->player.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	init_ray_step(game, r);
}

static void	check_door_hit(t_game *game, t_raycast *r)
{
	r->door_idx = door_idx(game, r->map_x, r->map_y);
	if (r->door_idx != -1 && game->doors[r->door_idx].state != 2)
	{
		if (r->side == 0)
			r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
		else
			r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
		if (r->side == 0)
			r->hit_pos = game->player.y + r->perp_wall_dist * r->ray_dir_y;
		else
			r->hit_pos = game->player.x + r->perp_wall_dist * r->ray_dir_x;
		r->hit_pos -= floor(r->hit_pos);
		if (r->hit_pos >= game->doors[r->door_idx].open_amount
			&& r->hit_pos < 1.0)
		{
			r->hit = 1;
			r->is_door = 1;
		}
	}
}

static void	perform_dda(t_game *game, t_raycast *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (game->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
		else if (game->map[r->map_y][r->map_x] == 'D')
			check_door_hit(game, r);
	}
}

int	raycasting(t_game *game)
{
	t_raycast	r;
	double		p_angle;

	p_angle = atan2(game->player.dir_y, game->player.dir_x);
	if (p_angle < 0)
		p_angle += 2 * M_PI;
	r.sky_offset_x = (int)((p_angle / (2 * M_PI)) * game->sky_img.width);
	r.x = 0;
	while (r.x < 1920)
	{
		init_ray(game, &r);
		perform_dda(game, &r);
		calc_projection(game, &r);
		draw_vertical_line(game, &r);
		r.x++;
	}
	render_sprite(game);
	if (game->player.torch == 0)
		render_torch(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen.img, 0,
		0);
	return (1);
}
