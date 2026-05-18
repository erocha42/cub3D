/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:37:56 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/18 18:33:08 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_move_speed(t_game *game)
{
	double	speed;

	speed = 0.1;
	if (game->player.sprint == 1)
		speed = 0.18;
	if (game->player.torch == 1)
		speed = speed / 1.5;
	return (speed);
}

void	move_fb(t_game *game, double speed)
{
	if (is_walkable(game, game->player.x + game->player.dir_x * speed,
			game->player.y))
		game->player.x += game->player.dir_x * speed;
	if (is_walkable(game, game->player.x, game->player.y + game->player.dir_y
			* speed))
		game->player.y += game->player.dir_y * speed;
	if (game->has_audio == 1)
	{
		ma_sound_start(&game->step_sound);
		ma_sound_set_volume(&game->step_sound, 5);
	}
}

void	move_lr(t_game *game, double speed)
{
	if (is_walkable(game, game->player.x + game->player.dir_y * speed,
			game->player.y))
		game->player.x += game->player.dir_y * speed;
	if (is_walkable(game, game->player.x, game->player.y - game->player.dir_x
			* speed))
		game->player.y -= game->player.dir_x * speed;
	if (game->has_audio == 1)
	{
		ma_sound_start(&game->step_sound);
		ma_sound_set_volume(&game->step_sound, 5);
	}
}

void	rotate_player_key(t_game *game, double rot)
{
	double	old_dir;
	double	old_plane;

	old_dir = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot) - game->player.dir_y
		* sin(rot);
	game->player.dir_y = old_dir * sin(rot) + game->player.dir_y * cos(rot);
	old_plane = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane * sin(rot) + game->player.plane_y
		* cos(rot);
}
