/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:19:57 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/05 14:35:57 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_hook(t_game *game)
{
	int		delta;
	double	res;
	int		x;
	int		y;
	double	OldDirX;
	double	OldPlaneX;

	delta = 0;
	res = 0;
	x = 0;
	y = 0;
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &x, &y);
	delta = x - 960;
	res = 0.005 * delta;
	OldDirX = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(res) - game->player.dir_y
		* sin(res);
	game->player.dir_y = OldDirX * sin(res) + game->player.dir_y * cos(res);
	OldPlaneX = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(res)
		- game->player.plane_y * sin(res);
	game->player.plane_y = OldPlaneX * sin(res) + game->player.plane_y
		* cos(res);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, 960, 540);
}
