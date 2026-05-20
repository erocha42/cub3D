/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:19:57 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/20 15:37:08 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	rotate_player(t_game *game, double res)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(res) - game->player.dir_y
		* sin(res);
	game->player.dir_y = old_dir_x * sin(res) + game->player.dir_y * cos(res);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(res)
		- game->player.plane_y * sin(res);
	game->player.plane_y = old_plane_x * sin(res) + game->player.plane_y
		* cos(res);
}

void	mouse_hook(t_game *game)
{
	int	x;
	int	y;
	int	delta;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &x, &y);
	delta = x - game->player.last_x;
	if (delta == 0)
		return ;
	game->player.last_x = x;
	rotate_player(game, delta * 0.001);
	if (x < 100 || x > 1800)
	{
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, 960, 540);
		game->player.last_x = 960;
	}
}
