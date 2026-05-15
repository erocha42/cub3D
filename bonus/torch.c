/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:23:16 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 13:12:14 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	apply_shadow(int color, double intensity)
{
	int	r;
	int	g;
	int	b;

	if (intensity <= 0)
		return (0x000000);
	if (intensity >= 1)
		return (color);
	r = ((color >> 16) & 0xFF) * intensity;
	g = ((color >> 8) & 0xFF) * intensity;
	b = (color & 0xFF) * intensity;
	return ((r << 16) | (g << 8) | b);
}

void	render_torch(t_game *game)
{
	int		x;
	int		y;
	int		dist_sq;
	int		color;
	double	intensity;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			dist_sq = ((x - 960) * (x - 960)) + ((y - 540) * (y - 540));
			if (dist_sq >= 250000)
				my_mlx_pixel_put(game, x, y, 0x000000);
			else if (dist_sq > 10000)
			{
				intensity = 1.0 - ((double)(dist_sq - 10000) / 240000);
				color = get_tex_color(&game->screen, x, y);
				color = apply_shadow(color, intensity);
				my_mlx_pixel_put(game, x, y, color);
			}
			x++;
		}
		y++;
	}
}
