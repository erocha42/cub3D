/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:41:30 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/12 16:05:30 by mchesnea         ###   ########.fr       */
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
			if (game->map[i][j] == '0' || game->map[i][j] == 'N'
				|| game->map[i][j] == 'S' || game->map[i][j] == 'E'
				|| game->map[i][j] == 'W')
				heatmap[i][j] = -1;
			else
				heatmap[i][j] = -2;
			j++;
		}
		i++;
	}
	return (heatmap);
}

int	**bfs(t_game *game)
{
	int	*queue;
	int	first;
	int	last;
	int	**map;
	int	cur_x;
	int	cur_y;
	int	i;
	int	dir_x[4] = {1, -1, 0, 0};
	int	dir_y[4] = {0, 0, 1, -1};
	int	new_x;
	int	new_y;

	first = 0;
	last = 0;
	map = heatmap(game);
	if (!map)
		return (NULL);
	map[(int)game->player.y][(int)game->player.x] = 0;
	queue = malloc((game->map_height * game->map_width) * sizeof(int));
	if (!queue)
		return (NULL);
	queue[last] = (int)game->player.y * game->map_width + (int)game->player.x;
	last++;
	while (first < last)
	{
		cur_x = queue[first] % game->map_width;
		cur_y = queue[first] / game->map_width;
		i = 0;
		while (i < 4)
		{
			new_x = cur_x + dir_x[i];
			new_y = cur_y + dir_y[i];
			if (new_x >= 0 && new_x < game->map_width && new_y >= 0
				&& new_y < game->map_height)
			{
				if (map[new_y][new_x] == -1)
				{
					map[new_y][new_x] = map[cur_y][cur_x] + 1;
					queue[last++] = new_y * game->map_width + new_x;
				}
			}
			i++;
		}
		first++;
	}
	free(queue);
	return (map);
}

void	get_next_step(t_game *game, int mx, int my, int *tx, int *ty)
{
	int **map;
	int dir_x[4] = {1, -1, 0, 0};
	int dir_y[4] = {0, 0, 1, -1};
	int new_x;
	int new_y;
	int i;
	int min_dist;

	min_dist = INT_MAX;
	*tx = mx;
	*ty = my;
	map = bfs(game);
	i = 0;
	while (i < 4)
	{
		new_x = mx + dir_x[i];
		new_y = my + dir_y[i];
		if (new_x >= 0 && new_x < game->map_width && new_y >= 0
			&& new_y < game->map_height)
		{
			if (map[new_y][new_x] >= 0 && map[new_y][new_x] < min_dist)
			{
				min_dist = map[new_y][new_x];
				*tx = new_x;
				*ty = new_y;
			}
		}
		i++;
	}
	free_tab_int(map, game->map_height);
}
