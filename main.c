/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:43:23 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/28 11:46:54 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_hook(int keycode, t_game *game)
{
	double	MoveSpeed;
	double	RotSpeed;
	double	OldDirX;
	double	OldPlaneX;

	MoveSpeed = 0.5;
	RotSpeed = 0.3;
	if (keycode == 119)
	{
		game->player.x += game->player.dir_x * MoveSpeed;
		game->player.y += game->player.dir_y * MoveSpeed;
	}
	if (keycode == 115)
	{
		game->player.x -= game->player.dir_x * MoveSpeed;
		game->player.y -= game->player.dir_y * MoveSpeed;
	}
	if (keycode == 97)
	{
		game->player.x -= game->player.dir_y * MoveSpeed;
		game->player.y += game->player.dir_x * MoveSpeed;
	}
	if (keycode == 100)
	{
		game->player.x += game->player.dir_y * MoveSpeed;
		game->player.y -= game->player.dir_x * MoveSpeed;
	}
	if (keycode == 65361)
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
	if (keycode == 65363)
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
	//char *dummy_map[] = {
    //    "111111111111111",
    //    "100000000000001",
    //    "100011111110001",
    //    "100010000010001",
    //    "100010000010001",
    //    "100011000110001",
    //    "100000000000001",
    //    "100000000000001",
    //    "111111101111111",
    //    "100000000000001",
    //    "100000000000001",
    //    "100100010001001",
    //    "100000000000001",
    //    "100100010001001",
    //    "111111111111111"
	//};

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
	//game.map = dummy_map;
	//game.player.x = 2.5;
	//game.player.y = 1.5;
	//game.player.dir_x = -1.0;
	//game.player.dir_y = 0.0;
	//game.player.plane_x = 0.0;
	//game.player.plane_y = 0.66;
	//game.n_path = "./sprites/wall1.xpm";
    //game.s_path = "./sprites/wall2.xpm";
    //game.e_path = "./sprites/wall3.xpm";
    //game.w_path = "./sprites/wall4.xpm";
	//// init_game(&game);
	if (init_mlx(&game) == 0)
		return (0);
	if (init_images(&game) == 0)
		return 0;
	raycasting(&game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_hook, &game);
	mlx_loop(game.mlx_ptr);
	clean_exit(&game, NO_ERROR);
	return (1);
}
