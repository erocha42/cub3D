/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:43:23 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/18 13:45:21 by mchesnea         ###   ########.fr       */
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
	if (keycode == 65505)
		game->player.sprint = 1;
	if (keycode == 102)
		game->player.torch = !game->player.torch;
	if (keycode == 101)
		interact_door(game);
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
	if (keycode == 65505)
		game->player.sprint = 0;
	return (0);
}

int	game_loop(t_game *game)
{
	double	move_speed;

	move_speed = get_move_speed(game);
	if (game->player.move_up == 1)
		move_fb(game, move_speed);
	if (game->player.move_down == 1)
		move_fb(game, -move_speed);
	if (game->player.move_left == 1)
		move_lr(game, move_speed);
	if (game->player.move_right == 1)
		move_lr(game, -move_speed);
	if (game->player.rotate_left == 1)
		rotate_player_key(game, 0.1);
	if (game->player.rotate_right == 1)
		rotate_player_key(game, -0.1);
	mouse_hook(game);
	if (game->sprite.x != -1)
		update_sprite(game);
	update_doors_animation(game);
	raycasting(game);
	return (0);
}

int	main(int ac, char *av[])
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Error:\n Bad Number Of Arguments\n", 2);
		return (0);
	}
	init_game(&game);
	parsing(av, &game);
	doors(&game);
	init_player_cam(&game);
	if (init_mlx(&game) == 0 || init_images(&game) == 0)
		return (0);
	if (game.sprite.x != -1)
		init_audio(&game);
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
