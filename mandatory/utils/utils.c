/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:23:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/20 17:06:54 by mchesnea         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->screen.addr + (y * game->screen.line_len + x * (game->screen.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_tex_color(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	process_trim(t_game *game, int c[6])
{
	if (c[0] > 2 || c[1] > 2 || c[2] > 2 || c[3] > 2 || c[4] > 2 || c[5] > 2)
		clean_exit(game, DATA_ERROR);
	data_recovery(game, skip(game->trim), c);
	free(game->trim);
	game->trim = NULL;
}
