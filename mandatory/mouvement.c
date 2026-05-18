/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:48:27 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/18 13:55:15 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_fb(t_game *game, double speed)
{
	if (game->map[(int)game->player.y][(int)(game->player.x + game->player.dir_x
		* speed)] != '1')
		game->player.x += game->player.dir_x * speed;
	if (game->map[(int)(game->player.y + game->player.dir_y
			* speed)][(int)game->player.x] != '1')
		game->player.y += game->player.dir_y * speed;
}

void	move_lr(t_game *game, double speed)
{
	if (game->map[(int)game->player.y][(int)(game->player.x + game->player.dir_y
		* speed)] != '1')
		game->player.x += game->player.dir_y * speed;
	if (game->map[(int)(game->player.y - game->player.dir_x
			* speed)][(int)game->player.x] != '1')
		game->player.y -= game->player.dir_x * speed;
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
