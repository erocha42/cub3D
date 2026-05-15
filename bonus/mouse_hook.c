/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:19:57 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 13:42:06 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_hook(t_game *game)
{
	int		x;
	int		y;
	int		delta;
	double	res;
	double	olddirx;
	double	oldplanex;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &x, &y);
	delta = x - game->player.last_x;
	game->player.last_x = x;
	if (delta == 0)
		return ;
	res = delta * 0.001;
	olddirx = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(res) - game->player.dir_y
		* sin(res);
	game->player.dir_y = olddirx * sin(res) + game->player.dir_y * cos(res);
	oldplanex = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(res)
		- game->player.plane_y * sin(res);
	game->player.plane_y = oldplanex * sin(res) + game->player.plane_y
		* cos(res);
	if (x < 100 || x > 1800)
	{
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, 960, 540);
		game->player.last_x = 960;
	}
}
