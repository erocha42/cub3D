/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:54:01 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/13 15:24:56 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_sprite(t_game *game)
{
	double	dist_euclid;
	double	dist_target;
	double	StepX;
	double	StepY;
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
		printf("GAME OVER\n");
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
		StepX = ((target_x)-game->sprite.x) / dist_target * 0.05;
		StepY = ((target_y)-game->sprite.y) / dist_target * 0.05;
		game->sprite.x += StepX;
		game->sprite.y += StepY;
	}
}

void	render_sprite(t_game *game)
{
	double	SpriteX;
	double	SpriteY;
	double	InvDet;
	double	TransformX;
	double	TransformY;
	int		SpriteScreenX;
	int		SpriteDimension;
	int		DrawStartY;
	int		DrawEndY;
	int		DrawStartX;
	int		DrawEndX;
	int		stripe;
	int		y;
	int		TexX;
	int		d;
	int		TexY;
	int		color;

	SpriteX = game->sprite.x - game->player.x;
	SpriteY = game->sprite.y - game->player.y;
	InvDet = 1 / (game->player.plane_x * game->player.dir_y - game->player.dir_x
			* game->player.plane_y);
	TransformX = InvDet * (game->player.dir_y * SpriteX - game->player.dir_x
			* SpriteY);
	TransformY = InvDet * (-game->player.plane_y * SpriteX
			+ game->player.plane_x * SpriteY);
	if (TransformY <= 0)
		return ;
	SpriteScreenX = (int)(1920 / 2) * (1 + TransformX / TransformY);
	SpriteDimension = abs((int)(1080 / TransformY));
	DrawStartY = -SpriteDimension / 2 + 1080 / 2;
	if (DrawStartY < 0)
		DrawStartY = 0;
	DrawEndY = SpriteDimension / 2 + 1080 / 2;
	if (DrawEndY >= 1080)
		DrawEndY = 1080 - 1;
	DrawStartX = -SpriteDimension / 2 + SpriteScreenX;
	if (DrawStartX < 0)
		DrawStartX = 0;
	DrawEndX = SpriteDimension / 2 + SpriteScreenX;
	if (DrawEndX > 1920)
		DrawEndX = 1920;
	stripe = DrawStartX;
	while (stripe < DrawEndX)
	{
		TexX = (stripe - (-SpriteDimension / 2 + SpriteScreenX)) * 200
			/ SpriteDimension;
		if (TexX < 0)
			TexX = 0;
		if (TexX >= 200)
			TexX = 199;
		if (TransformY < game->z_buffer[stripe] && TransformY > 0)
		{
			y = DrawStartY;
			while (y < DrawEndY)
			{
				d = y - 1080 / 2 + SpriteDimension / 2;
				TexY = (d * 200) / SpriteDimension;
				if (TexY < 0)
					TexY = 0;
				if (TexY >= 200)
					TexY = 199;
				color = get_tex_color(&game->tex_sprite, TexX, TexY);
				if (color != 0)
					my_mlx_pixel_put(game, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}
