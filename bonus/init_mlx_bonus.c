/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:22:30 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/20 15:37:01 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	close_window(t_game *game)
{
	clean_exit(game, NO_ERROR);
	return (0);
}

static int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		clean_exit(game, NO_ERROR);
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "Cub3D");
	if (!game->win_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return (0);
	}
	game->screen.img = mlx_new_image(game->mlx_ptr, 1920, 1080);
	if (!game->screen.img)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		return (0);
	}
	game->screen.addr = mlx_get_data_addr(game->screen.img, &game->screen.bpp,
			&game->screen.line_len, &game->screen.endian);
	mlx_key_hook(game->win_ptr, key_hook, game);
	mlx_hook(game->win_ptr, 17, 0, close_window, game);
	return (1);
}
