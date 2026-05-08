/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:41:30 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/08 17:59:59 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**heatmap(t_game *game)
{
	int	**heatmap;
	int	i;
	int	j;

	i = 0;
	heatmap = malloc(sizeof(int *) * game->map_height);
	if (!heatmap)
		return (NULL);
	while (i < game->map_height)
	{
		j = 0;
		heatmap[i] = malloc(sizeof(int) * game->map_width);
		if (!heatmap[i])
		{
			free_tab_int(heatmap, i);
			return (NULL);
		}
		while (j < game->map_width)
		{
			if (game->map[i][j] == '0')
				heatmap[i][j] = -1;
			else if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				heatmap[i][j] = 0;
			else
				heatmap[i][j] = -2;
			j++;
		}
		i++;
	}
	return (heatmap);
}

void	bfs(t_game *game)
{
	int *queue;
	int first;
	int last;
	int **map;
	int	cur_x;
	int	cur_y;

	first = 0;
	last = 0;
	map = heatmap(game);
	queue = malloc((game->map_height * game->map_width) * sizeof(int));
	queue[last] = (int)game->player.y * game->map_width + (int)game->player.x;
	last++;
	while (first < last)
	{
		cur_x = queue[first] % game->map_width;
		cur_y = queue[first] / game->map_width;
		
		first++;
	}
}