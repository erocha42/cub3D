/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:23:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/15 16:17:51 by mchesnea         ###   ########.fr       */
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

void	heatmap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->heatmap = malloc(sizeof(int *) * game->map_height);
	if (!game->heatmap)
		return ;
	while (i < game->map_height)
	{
		j = 0;
		game->heatmap[i] = malloc(sizeof(int) * game->map_width);
		if (!game->heatmap[i])
		{
			free_tab_int(game->heatmap, i);
			return ;
		}
		while (j < game->map_width)
		{
			if (is_walkable(game, j, i) == 1)
				game->heatmap[i][j++] = -1;
			else
				game->heatmap[i][j++] = -2;
		}
		i++;
	}
}

void	jumpscare(t_game *game)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	x = -1;
	while (++x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			tex_x = (x * game->tex_sprite.width) / 1920;
			tex_y = (y * game->tex_sprite.height) / 1080;
			if (tex_x >= game->tex_sprite.width)
				tex_x = game->tex_sprite.width - 1;
			if (tex_y >= game->tex_sprite.height)
				tex_y = game->tex_sprite.height - 1;
			color = get_tex_color(&game->tex_sprite, tex_x, tex_y);
			my_mlx_pixel_put(game, x, y++, color);
		}
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen.img, 0,
		0);
	mlx_do_sync(game->mlx_ptr);
}
