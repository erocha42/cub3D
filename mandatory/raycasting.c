/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:55:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/16 15:52:39 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->screen.addr + (y * game->screen.line_len + x * (game->screen.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	raycasting(t_game *game)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		DrawStart;
	int		DrawEnd;
	int		y;
	int		color;

	x = 0;
	while (x < 1920)
	{
		cameraX = 2 * x / (double)1920 - 1;
		rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
		mapX = (int)game->player.x;
		mapY = (int)game->player.y;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		hit = 0;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1 - game->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1 - game->player.y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		lineHeight = (int)(1080 / perpWallDist);
		DrawStart = (lineHeight * -1) / 2 + 1080 / 2;
		if (DrawStart < 0)
			DrawStart = 0;
		DrawEnd = lineHeight / 2 + 1080 / 2;
		if (DrawEnd >= 1080)
			DrawEnd = 1080 - 1;
		y = 0;
		while (y < DrawStart)
		{
			my_mlx_pixel_put(game, x, y, game->ceiling_color);
			y++;
		}
		if (side == 0)
			color = 0xFF0000;
		else
			color = 0x0000FF;
		while (y <= DrawEnd)
		{
			my_mlx_pixel_put(game, x, y, color);
			y++;
		}
		while (y < 1080)
		{
			my_mlx_pixel_put(game, x, y, game->ground_color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen.img, 0,
		0);
}
