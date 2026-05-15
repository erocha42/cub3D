/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:23:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/15 13:07:21 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_int(int **tab, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_walkable(t_game *game, double x, double y)
{
	int	idx;

	if (game->map[(int)y][(int)x] == '1')
		return (0);
	if (game->map[(int)y][(int)x] == 'D')
	{
		idx = door_idx(game, (int)x, (int)y);
		if (idx != -1 && game->doors[idx].state == 0)
			return (0);
	}
	return (1);
}
