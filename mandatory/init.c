/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:05:17 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/17 18:15:07 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->mlx_ptr = NULL;
	game->map = NULL;
	game->player.y = -1;
	game->player.x = -1;
	game->map_height = 0;
	game->map_width = 0;
	game->fd = -1;
	game->trim = NULL;
	game->n_path = NULL;
	game->s_path = NULL;
	game->w_path = NULL;
	game->e_path = NULL;
	game->direction_player = '\0';
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.move_up = 0;
	game->player.rotate_left = 0;
	game->player.rotate_right = 0;
}

static void	init_ew_cam(t_game *game)
{
	if (game->direction_player == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (game->direction_player == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
}

void	init_player_cam(t_game *game)
{
	if (game->direction_player == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->direction_player == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else
		init_ew_cam(game);
}
