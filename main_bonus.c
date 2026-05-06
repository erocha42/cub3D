/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:43:23 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/06 15:49:16 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hook(int keycode, t_game *game)
{
	double	MoveSpeed;
	double	RotSpeed;
	double	OldDirX;
	double	OldPlaneX;

	MoveSpeed = 0.3;
	RotSpeed = 0.2;
	if (keycode == 119)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				+ game->player.dir_x * MoveSpeed)] != '1')
			game->player.x += game->player.dir_x * MoveSpeed;
		if (game->map[(int)(game->player.y + game->player.dir_y
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y += game->player.dir_y * MoveSpeed;
	}
	if (keycode == 115)
	{
		if (keycode == 115)
		{
			if (game->map[(int)game->player.y][(int)(game->player.x
					- game->player.dir_x * MoveSpeed)] != '1')
				game->player.x -= game->player.dir_x * MoveSpeed;
			if (game->map[(int)(game->player.y - game->player.dir_y
					* MoveSpeed)][(int)game->player.x] != '1')
				game->player.y -= game->player.dir_y * MoveSpeed;
		}
	}
	if (keycode == 97)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				+ game->player.dir_y * MoveSpeed)] != '1')
			game->player.x += game->player.dir_y * MoveSpeed;
		if (game->map[(int)(game->player.y - game->player.dir_x
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y -= game->player.dir_x * MoveSpeed;
	}
	if (keycode == 100)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				- game->player.dir_y * MoveSpeed)] != '1')
			game->player.x -= game->player.dir_y * MoveSpeed;
		if (game->map[(int)(game->player.y + game->player.dir_x
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y += game->player.dir_x * MoveSpeed;
	}
	if (keycode == 65363)
	{
		OldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(RotSpeed)
			- game->player.dir_y * sin(RotSpeed);
		game->player.dir_y = OldDirX * sin(RotSpeed) + game->player.dir_y
			* cos(RotSpeed);
		OldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(RotSpeed)
			- game->player.plane_y * sin(RotSpeed);
		game->player.plane_y = OldPlaneX * sin(RotSpeed) + game->player.plane_y
			* cos(RotSpeed);
	}
	if (keycode == 65361)
	{
		OldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(RotSpeed)
			+ game->player.dir_y * sin(RotSpeed);
		game->player.dir_y = -OldDirX * sin(RotSpeed) + game->player.dir_y
			* cos(RotSpeed);
		OldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(RotSpeed)
			+ game->player.plane_y * sin(RotSpeed);
		game->player.plane_y = -OldPlaneX * sin(RotSpeed) + game->player.plane_y
			* cos(RotSpeed);
	}
	raycasting(game);
	return (0);
}

int	main(int ac, char *av[])
{
	t_game	game;

	if (ac != 2)
	{
		if (ac < 2)
			ft_putstr_fd("Error: Not Enough Arguments\n", 2);
		else
			ft_putstr_fd("Error: Too Many Arguments\n", 2);
		return (0);
	}
	init_game(&game);
	parsing(av, &game);
	init_player_cam(&game);
	if (init_mlx(&game) == 0)
		return (0);
	if (init_images(&game) == 0)
		return (0);
	raycasting(&game);
	minimap(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_hook, &game);
	mlx_loop(game.mlx_ptr);
	clean_exit(&game, NO_ERROR);
	return (1);
}
