/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:28:39 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/17 18:16:16 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MAP_W_START 1700
#define MAP_W_LIMIT 1900
#define MAP_H_START 25
#define MAP_H_LIMIT 225

static void	put_square(t_game *game, int x_start, int y_start, int color)
{
	int	x;
	int	y;

	x_start = MAP_W_START + ((x_start - game->cam_x) * 20);
	y_start = MAP_H_START + ((y_start - game->cam_y) * 20);
	x = x_start;
	y = y_start;
	while (y < y_start + 20)
	{
		while (x < x_start + 20)
		{
			my_mlx_pixel_put(game, x, y, color);
			x++;
		}
		x = x_start;
		y++;
	}
}

static void	put_walls(t_game *game, int cam_x, int cam_y)
{
	int	cam_x_init;
	int	cam_y_init;
	int	color_wall;

	cam_x_init = cam_x;
	cam_y_init = cam_y;
	color_wall = color_recovery(game, "100,100,100");
	while (cam_y < cam_y_init + 10)
	{
		while (cam_x < cam_x_init + 10)
		{
			if (cam_x < game->map_width && cam_y < game->map_height
				&& game->map[cam_y][cam_x] == '1')
				put_square(game, cam_x, cam_y, color_wall);
			cam_x++;
		}
		cam_x = cam_x_init;
		cam_y++;
	}
}

static void	put_chars(t_game *game)
{
	int	color_player;

	color_player = color_recovery(game, "20,200,0");
	put_square(game, (int)game->player.x, (int)game->player.y, color_player);
}

static void	update_minimap_camera(t_game *game)
{
	if (game->cam_x > 0 && game->player.x < game->cam_x + 3)
		game->cam_x--;
	else if (game->map_width > game->cam_x + 10 && game->player.x > game->cam_x
		+ 7)
		game->cam_x++;
	if (game->cam_y > 0 && game->player.y < game->cam_y + 3)
		game->cam_y--;
	else if (game->map_height > game->cam_y + 10 && game->player.y > game->cam_y
		+ 7)
		game->cam_y++;
}

void	minimap(t_game *game)
{
	int	x;
	int	y;

	x = MAP_W_START;
	y = MAP_H_START;
	update_minimap_camera(game);
	while (y < MAP_H_LIMIT)
	{
		while (x < MAP_W_LIMIT)
		{
			my_mlx_pixel_put(game, x, y, game->ground_color);
			x++;
		}
		x = MAP_W_START;
		y++;
	}
	put_walls(game, game->cam_x, game->cam_y);
	put_chars(game);
}
