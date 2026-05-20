/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:07:37 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/20 15:37:15 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calc_tex_x(t_game *game, t_raycast *r)
{
	if (r->side == 0)
		r->wall_x = game->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = game->player.x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	if (r->is_door == 1)
	{
		r->wall_x -= game->doors[r->door_idx].open_amount;
		if (r->wall_x < 0.0)
			r->wall_x += 1.0;
	}
	r->tex_x = (int)(r->wall_x * 64.0);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = 64 - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = 64 - r->tex_x - 1;
	r->step = 1.0 * 64 / r->line_height;
	r->tex_pos = (r->draw_start - 1080 / 2.0 + r->line_height / 2.0) * r->step;
}

void	calc_projection(t_game *game, t_raycast *r)
{
	if (r->is_door == 0)
	{
		if (r->side == 0)
			r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
		else
			r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
	}
	game->z_buffer[r->x] = r->perp_wall_dist;
	r->line_height = (int)(1080 / r->perp_wall_dist);
	r->draw_start = (r->line_height * -1) / 2 + 1080 / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + 1080 / 2;
	if (r->draw_end >= 1080)
		r->draw_end = 1080 - 1;
	calc_tex_x(game, r);
}

static void	draw_wall(t_game *game, t_raycast *r)
{
	int	tex_y;
	int	color;

	while (r->y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= 64)
			tex_y = 63;
		r->tex_pos += r->step;
		if (game->map[r->map_y][r->map_x] == 'D')
			color = get_tex_color(&game->tex_d, r->tex_x, tex_y);
		else if (r->side == 0 && r->ray_dir_x > 0)
			color = get_tex_color(&game->tex_e, r->tex_x, tex_y);
		else if (r->side == 0 && r->ray_dir_x < 0)
			color = get_tex_color(&game->tex_w, r->tex_x, tex_y);
		else if (r->side == 1 && r->ray_dir_y > 0)
			color = get_tex_color(&game->tex_s, r->tex_x, tex_y);
		else
			color = get_tex_color(&game->tex_n, r->tex_x, tex_y);
		my_mlx_pixel_put(game, r->x, r->y, color);
		r->y++;
	}
}

void	draw_vertical_line(t_game *game, t_raycast *r)
{
	int	sky_tx;
	int	sky_ty;
	int	color;

	r->y = 0;
	while (r->y < r->draw_start)
	{
		sky_tx = (r->sky_offset_x + r->x) % game->sky_img.width;
		sky_ty = (r->y * game->sky_img.height) / (1080 / 2);
		color = get_tex_color(&game->sky_img, sky_tx, sky_ty);
		my_mlx_pixel_put(game, r->x, r->y, color);
		r->y++;
	}
	draw_wall(game, r);
	while (r->y < 1080)
	{
		my_mlx_pixel_put(game, r->x, r->y, game->ground_color);
		r->y++;
	}
}
