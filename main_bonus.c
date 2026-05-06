/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:43:23 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/06 18:23:52 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		clean_exit(game, NO_ERROR);
	if (keycode == 119)
		game->player.move_up = 1;
	if (keycode == 115)
		game->player.move_down = 1;
	if (keycode == 97)
		game->player.move_left = 1;
	if (keycode == 100)
		game->player.move_right = 1;
	if (keycode == 65363)
		game->player.rotate_left = 1;
	if (keycode == 65361)
		game->player.rotate_right = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->player.move_up = 0;
	if (keycode == 115)
		game->player.move_down = 0;
	if (keycode == 97)
		game->player.move_left = 0;
	if (keycode == 100)
		game->player.move_right = 0;
	if (keycode == 65363)
		game->player.rotate_left = 0;
	if (keycode == 65361)
		game->player.rotate_right = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	double	MoveSpeed;
	double	RotSpeed;
	double	OldDirX;
	double	OldPlaneX;

	MoveSpeed = 0.1;
	RotSpeed = 0.1;
	if (game->player.move_up == 1)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				+ game->player.dir_x * MoveSpeed)] != '1')
			game->player.x += game->player.dir_x * MoveSpeed;
		if (game->map[(int)(game->player.y + game->player.dir_y
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y += game->player.dir_y * MoveSpeed;
	}
	if (game->player.move_down == 1)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				- game->player.dir_x * MoveSpeed)] != '1')
			game->player.x -= game->player.dir_x * MoveSpeed;
		if (game->map[(int)(game->player.y - game->player.dir_y
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y -= game->player.dir_y * MoveSpeed;
	}
	if (game->player.move_left == 1)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				+ game->player.dir_y * MoveSpeed)] != '1')
			game->player.x += game->player.dir_y * MoveSpeed;
		if (game->map[(int)(game->player.y - game->player.dir_x
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y -= game->player.dir_x * MoveSpeed;
	}
	if (game->player.move_right == 1)
	{
		if (game->map[(int)game->player.y][(int)(game->player.x
				- game->player.dir_y * MoveSpeed)] != '1')
			game->player.x -= game->player.dir_y * MoveSpeed;
		if (game->map[(int)(game->player.y + game->player.dir_x
				* MoveSpeed)][(int)game->player.x] != '1')
			game->player.y += game->player.dir_x * MoveSpeed;
	}
	if (game->player.rotate_left == 1)
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
	if (game->player.rotate_right == 1)
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
	mouse_hook(game);
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
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win_ptr, 3, 1L << 1, key_release, &game);
	mlx_mouse_hide(game.mlx_ptr, game.win_ptr);
	mlx_mouse_move(game.mlx_ptr, game.win_ptr, 960, 540);
	game.player.last_x = 960;
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	clean_exit(&game, NO_ERROR);
	return (1);
}
