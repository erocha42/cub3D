/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:41:30 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/17 20:25:19 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_node(t_game *game, int *q, int *last, int n_c[3])
{
	int	cur_val;

	if (n_c[0] >= 0 && n_c[0] < game->map_width && n_c[1] >= 0
		&& n_c[1] < game->map_height)
	{
		if (game->heatmap[n_c[1]][n_c[0]] == -1)
		{
			cur_val = game->heatmap[n_c[2] / game->map_width][n_c[2]
				% game->map_width];
			game->heatmap[n_c[1]][n_c[0]] = cur_val + 1;
			q[*last] = n_c[1] * game->map_width + n_c[0];
			*last += 1;
		}
	}
}

static void	expand_node(t_game *game, int *q, int *last, int current)
{
	int	n_c[3];

	n_c[2] = current;
	n_c[0] = (current % game->map_width) + 1;
	n_c[1] = current / game->map_width;
	check_node(game, q, last, n_c);
	n_c[0] = (current % game->map_width) - 1;
	check_node(game, q, last, n_c);
	n_c[0] = current % game->map_width;
	n_c[1] = (current / game->map_width) + 1;
	check_node(game, q, last, n_c);
	n_c[1] = (current / game->map_width) - 1;
	check_node(game, q, last, n_c);
}

void	bfs(t_game *game)
{
	int	*queue;
	int	first;
	int	last;

	first = 0;
	last = 0;
	if (!game->heatmap || game->sprite.x == -1)
		return ;
	game->heatmap[(int)game->player.y][(int)game->player.x] = 0;
	queue = malloc((game->map_height * game->map_width) * sizeof(int));
	if (!queue)
		return ;
	queue[last] = (int)game->player.y * game->map_width + (int)game->player.x;
	last++;
	while (first < last)
	{
		expand_node(game, queue, &last, queue[first]);
		first++;
	}
	free(queue);
}

static void	check_step(t_game *game, int nx, int ny, int state[3])
{
	if (nx >= 0 && nx < game->map_width && ny >= 0 && ny < game->map_height)
	{
		if (game->heatmap[ny][nx] >= 0 && game->heatmap[ny][nx] < state[0])
		{
			state[0] = game->heatmap[ny][nx];
			state[1] = nx;
			state[2] = ny;
		}
	}
}

void	get_next_step(t_game *game, int mx, int my, int *t_xy)
{
	int	state[3];

	state[0] = INT_MAX;
	state[1] = mx;
	state[2] = my;
	if (!game->heatmap)
		return ;
	check_step(game, mx + 1, my, state);
	check_step(game, mx - 1, my, state);
	check_step(game, mx, my + 1, state);
	check_step(game, mx, my - 1, state);
	t_xy[0] = state[1];
	t_xy[1] = state[2];
}
