/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:15:37 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/30 12:43:15 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**map_cpy(t_game *game)
{
	int		i;
	int		j;
	char	**gridcpy;

	gridcpy = malloc(game->map_height * sizeof(char *));
	if (!gridcpy)
		clean_exit(game, MALLOC_ERROR);
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		gridcpy[i] = malloc(game->map_width * sizeof(char));
		if (!gridcpy[i])
			clean_exit(game, MALLOC_ERROR);
		while (j < game->map_width)
		{
			gridcpy[i][j] = game->map[i][j];
			j++;
		}
		i++;
	}
	return (gridcpy);
}

static void	flood_fill(t_game *game, char **grid, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map_height - 1 || x >= game->map_width - 1)
	{
		free_tab(grid, game->map_height);
		clean_exit(game, MAP_ERROR);
	}
	if (grid[y][x] == ' ' || grid[y][x] == '\0')
	{
		free_tab(grid, game->map_height);
		clean_exit(game, MAP_ERROR);
	}
	grid[y][x] = 'X';
	if (grid[y - 1][x] != '1' && grid[y - 1][x] != 'X')
		flood_fill(game, grid, y - 1, x);
	if (grid[y][x + 1] != '1' && grid[y][x + 1] != 'X')
		flood_fill(game, grid, y, x + 1);
	if (grid[y + 1][x] != '1' && grid[y + 1][x] != 'X')
		flood_fill(game, grid, y + 1, x);
	if (grid[y][x - 1] != '1' && grid[y][x - 1] != 'X')
		flood_fill(game, grid, y, x - 1);
	return ;
}

void	valid_map(t_game *game)
{
	char	**grid;

	grid = map_cpy(game);
	flood_fill(game, grid, (int)game->player.y, (int)game->player.x);
	free_tab(grid, game->map_height);
}
