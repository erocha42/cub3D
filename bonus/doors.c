/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:33:52 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/12 15:13:49 by erocha--         ###   ########.fr       */
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
				game->nb_doors++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	doors(t_game *game)
{
	doors_recovery(game);
}