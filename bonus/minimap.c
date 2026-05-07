/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:28:39 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/07 15:49:57 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MAP_W_START 1700
# define MAP_W_LIMIT 1900
# define MAP_H_START 25
# define MAP_H_LIMIT 225

static void	put_square(t_game *game, int x_start, int y_start, int color)
{
	int	x;
	int	y;

	x_start = MAP_W_START + (x_start * 20);
	y_start = MAP_H_START + (y_start * 20);
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

static void	put_walls(t_game *game)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = color_recovery(game, "100,100,100");
	while (y < (MAP_H_LIMIT - MAP_H_START) / 20)
	{
		while (x < (MAP_W_LIMIT - MAP_W_START) / 20)
		{
			if (game->map[y][x] == '1')
				put_square(game, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

static void	put_player(t_game *game)
{
	int	color_player;
	int	color_monster;

	color_player = color_recovery(game, "20,200,0");
	color_monster = color_recovery(game, "200,0,0");
	put_square(game, (int)game->player.x, (int)game->player.y, color_player);
	put_square(game, 1, 1, color_monster);
}

void	minimap(t_game *game)
{
	int	x;
	int	y;

	x = MAP_W_START;
	y = MAP_H_START;
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
	put_walls(game);
	put_player(game);
}
