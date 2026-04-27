/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:05:17 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/27 18:37:26 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	if (game->direction_player == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	if (game->direction_player == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	if (game->direction_player == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	if (game->direction_player == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
}

static int	close_window(t_game *game)
{
	if (game->screen.img)
		mlx_destroy_image(game->mlx_ptr, game->screen.img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
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
