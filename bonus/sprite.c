/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 17:54:01 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/12 17:20:58 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_sprite(t_game *game)
{
	double	Dist;
	double	StepX;
	double	StepY;
	double	Old_X;
	double	Old_Y;
	int		tx;
	int		ty;
	double	target_x;
	double	target_y;
	float	volume;

	tx = 0;
	ty = 0;
	Old_X = game->sprite.x;
	Old_Y = game->sprite.y;
	Dist = sqrt(pow(game->player.x - game->sprite.x, 2) + pow(game->player.y
				- game->sprite.y, 2));
	if (Dist < 0.3)
	{
		printf("GAME OVER\n");
		clean_exit(game, NO_ERROR);
	}
	if (Dist > 15.0)
		volume = 0.0f;
	else
		volume = 1.0f - (Dist / 15.0);
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
	Dist = sqrt(pow(target_x - game->sprite.x, 2) + pow(target_y
				- game->sprite.y, 2));
	if (Dist > 0.05)
	{
		StepX = ((target_x)-game->sprite.x) / Dist * 0.05;
		StepY = ((target_y)-game->sprite.y) / Dist * 0.05;
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
