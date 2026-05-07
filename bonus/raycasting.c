/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:55:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/07 18:47:02 by mchesnea         ###   ########.fr       */
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

int	get_tex_color(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	raycasting(t_game *game)
{
	int x;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int DrawStart;
	int DrawEnd;
	int y;
	int color;
	double wallX;
	int texX;
	double step;
	int texY;
	double texPos;

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
		game->z_buffer[x] = perpWallDist;
		lineHeight = (int)(1080 / perpWallDist);
		DrawStart = (lineHeight * -1) / 2 + 1080 / 2;
		if (DrawStart < 0)
			DrawStart = 0;
		DrawEnd = lineHeight / 2 + 1080 / 2;
		if (DrawEnd >= 1080)
			DrawEnd = 1080 - 1;
		if (side == 0)
			wallX = game->player.y + perpWallDist * rayDirY;
		else
			wallX = game->player.x + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		texX = (int)(wallX * 64);
		if (side == 0 && rayDirX > 0)
			texX = 64 - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = 64 - texX - 1;
		step = 1.0 * 64 / lineHeight;
		texPos = (DrawStart - 1080 / 2.0 + lineHeight / 2.0) * step;
		y = 0;
		while (y < DrawStart)
		{
			my_mlx_pixel_put(game, x, y, game->ceiling_color);
			y++;
		}
		while (y <= DrawEnd)
		{
			texY = (int)texPos;
			if (texY < 0)
				texY = 0;
			else if (texY >= 64)
				texY = 64 - 1;
			texPos += step;
			if (side == 0 && rayDirX > 0)
				color = get_tex_color(&game->tex_e, texX, texY);
			else if (side == 0 && rayDirX < 0)
				color = get_tex_color(&game->tex_w, texX, texY);
			else if (side == 1 && rayDirY > 0)
				color = get_tex_color(&game->tex_s, texX, texY);
			else
				color = get_tex_color(&game->tex_n, texX, texY);
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
<<<<<<< HEAD
	minimap(game);
=======
	render_sprite(game);
>>>>>>> 3a87077 (add sprite with texture)
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen.img, 0,
		0);
	return (1);
}
