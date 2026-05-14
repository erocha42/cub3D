/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:33:52 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/14 15:56:10 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	doors_recovery(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->doors = malloc(sizeof(t_doors) * game->map_height * game->map_width);
	if (!game->doors)
		clean_exit(game, MALLOC_ERROR);
	game->nb_doors = 0;
	while (y < game->map_height)
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'D')
			{
				game->doors[game->nb_doors].state = 0;
				game->doors[game->nb_doors].x = x;
				game->doors[game->nb_doors].y = y;
				game->doors[game->nb_doors].open_amount = 0;
				game->nb_doors++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

int	door_idx(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->nb_doors)
	{
		if (game->doors[i].x == x && game->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

void	interact_door(t_game *game)
{
	int	target_x;
	int	target_y;
	int	idx;

	target_x = (int)(game->player.x + game->player.dir_x);
	target_y = (int)(game->player.y + game->player.dir_y);
	if (game->map[target_y][target_x] == 'D')
	{
		idx = door_idx(game, target_x, target_y);
		if (idx != -1)
		{
			if (game->doors[idx].state == 0)
				game->doors[idx].state = 1;
			else if (game->doors[idx].state == 2)
				game->doors[idx].state = 3;
		}
	}
}

void	update_doors_animation(t_game *game)
{
	int		i;
	double	speed;

	i = 0;
	speed = 0.05;
	while (i < game->nb_doors)
	{
		if (game->doors[i].state == 1)
		{
			game->doors[i].open_amount += speed;
			if (game->doors[i].open_amount >= 1.0)
			{
				game->doors[i].open_amount = 1.0;
				game->doors[i].state = 2;
			}
		}
		else if (game->doors[i].state == 3)
		{
			game->doors[i].open_amount -= speed;
			if (game->doors[i].open_amount <= 0.0)
			{
				game->doors[i].open_amount = 0.0;
				game->doors[i].state = 0;
			}
		}
		i++;
	}
}

void	doors(t_game *game)
{
	doors_recovery(game);
}