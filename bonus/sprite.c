/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:54:01 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 13:42:42 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jumpscare(t_game *game)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	x = -1;
	while (++x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			tex_x = (x * game->tex_sprite.width) / 1920;
			tex_y = (y * game->tex_sprite.height) / 1080;
			if (tex_x >= game->tex_sprite.width)
				tex_x = game->tex_sprite.width - 1;
			if (tex_y >= game->tex_sprite.height)
				tex_y = game->tex_sprite.height - 1;
			color = get_tex_color(&game->tex_sprite, tex_x, tex_y);
			my_mlx_pixel_put(game, x, y++, color);
		}
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen.img, 0,
		0);
	mlx_do_sync(game->mlx_ptr);
}

void	update_sprite(t_game *game)
{
	double	dist_euclid;
	double	dist_target;
	double	stepx;
	double	stepy;
	int		tx;
	int		ty;
	double	target_x;
	double	target_y;
	float	volume;
	int		bfs_dist;

	tx = 0;
	ty = 0;
	dist_euclid = sqrt(pow(game->player.x - game->sprite.x, 2)
			+ pow(game->player.y - game->sprite.y, 2));
	if (dist_euclid < 0.3)
	{
		jumpscare(game);
		ma_sound_set_volume(&game->monster_sound, 0);
		ma_sound_start(&game->jumpscare_sound);
		usleep(2000000);
		clean_exit(game, NO_ERROR);
	}
	if (game->heatmap)
		free_tab_int(game->heatmap, game->map_height);
	heatmap(game);
	bfs(game);
	bfs_dist = game->heatmap[(int)game->sprite.y][(int)game->sprite.x];
	if (bfs_dist > 15 || bfs_dist < 0)
		volume = 0.0f;
	else
		volume = 1.0f - ((float)bfs_dist / 15.0f);
	if (volume < 0.0f)
		volume = 0.0f;
	if (volume > 1.0f)
		volume = 1.0f;
	if (game->has_audio == 1)
		ma_sound_set_volume(&game->monster_sound, volume);
	if ((int)game->sprite.x == (int)game->player.x
		&& (int)game->sprite.y == (int)game->player.y)
	{
		target_x = game->player.x;
		target_y = game->player.y;
	}
	else
	{
		get_next_step(game, (int)game->sprite.x, (int)game->sprite.y, &tx, &ty);
		target_x = tx + 0.5;
		target_y = ty + 0.5;
	}
	dist_target = sqrt(pow(target_x - game->sprite.x, 2) + pow(target_y
				- game->sprite.y, 2));
	if (dist_target > 0.05)
	{
		stepx = ((target_x)-game->sprite.x) / dist_target * 0.05;
		stepy = ((target_y)-game->sprite.y) / dist_target * 0.05;
		game->sprite.x += stepx;
		game->sprite.y += stepy;
	}
}

void	render_sprite(t_game *game)
{
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spritedimension;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
	int		stripe;
	int		y;
	int		texx;
	int		d;
	int		texy;
	int		color;

	spritex = game->sprite.x - game->player.x;
	spritey = game->sprite.y - game->player.y;
	invdet = 1 / (game->player.plane_x * game->player.dir_y - game->player.dir_x
			* game->player.plane_y);
	transformx = invdet * (game->player.dir_y * spritex - game->player.dir_x
			* spritey);
	transformy = invdet * (-game->player.plane_y * spritex
			+ game->player.plane_x * spritey);
	if (transformy <= 0)
		return ;
	spritescreenx = (int)(1920 / 2) * (1 + transformx / transformy);
	spritedimension = abs((int)(1080 / transformy));
	drawstarty = -spritedimension / 2 + 1080 / 2;
	if (drawstarty < 0)
		drawstarty = 0;
	drawendy = spritedimension / 2 + 1080 / 2;
	if (drawendy >= 1080)
		drawendy = 1080 - 1;
	drawstartx = -spritedimension / 2 + spritescreenx;
	if (drawstartx < 0)
		drawstartx = 0;
	drawendx = spritedimension / 2 + spritescreenx;
	if (drawendx > 1920)
		drawendx = 1920;
	stripe = drawstartx;
	while (stripe < drawendx)
	{
		texx = (stripe - (-spritedimension / 2 + spritescreenx)) * 200
			/ spritedimension;
		if (texx < 0)
			texx = 0;
		if (texx >= 200)
			texx = 199;
		if (transformy < game->z_buffer[stripe] && transformy > 0)
		{
			y = drawstarty;
			while (y < drawendy)
			{
				d = y - 1080 / 2 + spritedimension / 2;
				texy = (d * 200) / spritedimension;
				if (texy < 0)
					texy = 0;
				if (texy >= 200)
					texy = 199;
				color = get_tex_color(&game->tex_sprite, texx, texy);
				if (color != 0)
					my_mlx_pixel_put(game, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}
