/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:15:37 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/19 17:35:38 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**map_cpy(t_game *game)
{
	int		i;
	int		j;
	char	**gridcpy;

	gridcpy = malloc((game->map_height + 1) * sizeof(char *));
	if (!gridcpy)
		clean_exit(game, MALLOC_ERROR);
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		gridcpy[i] = malloc((game->map_width + 1) * sizeof(char));
		if (!gridcpy[i])
			clean_exit(game, MALLOC_ERROR);
		while (j < game->map_width)
		{
			gridcpy[i][j] = game->map[i][j];
			j++;
		}
		gridcpy[i][j] = '\0';
		i++;
	}
	gridcpy[i] = NULL;
	return (gridcpy);
}

static void	flood_fill(t_game *game, char **grid, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map_height || x >= game->map_width)
	{
		free_tab(grid, game->map_height);
		clean_exit(game, MAP_ERROR);
	}
	if (grid[y][x] == ' ' || grid[y][x] == '\0')
	{
		free_tab(grid, game->map_height);
		clean_exit(game, MAP_ERROR);
	}
	if (grid[y][x] == '1' || grid[y][x] == 'X')
		return ;
	grid[y][x] = 'X';
	flood_fill(game, grid, y - 1, x);
	flood_fill(game, grid, y + 1, x);
	flood_fill(game, grid, y, x - 1);
	flood_fill(game, grid, y, x + 1);
	return ;
}

void	valid_map(t_game *game)
{
	char	**grid;
	int		x;
	int		y;

	x = 0;
	y = 0;
	grid = map_cpy(game);
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '0' || grid[y][x] == 'N' || grid[y][x] == 'S'
				|| grid[y][x] == 'E' || grid[y][x] == 'W')
				flood_fill(game, grid, y, x);
			x++;
		}
		y++;
	}
	free_tab(grid, game->map_height);
}
