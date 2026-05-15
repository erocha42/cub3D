/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:55:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/15 13:38:54 by mchesnea         ###   ########.fr       */
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
	double	player_angle;
	int		sky_offset_x;
	int		sky_texx;
	int		sky_texy;
	int		x;
	int		idx;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		y;
	int		color;
	double	wallx;
	int		texx;
	double	step;
	int		texy;
	double	texpos;
	double	hitpos;
	int		is_door_hit;

	x = 0;
	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	if (player_angle < 0)
		player_angle += 2 * M_PI;
	sky_offset_x = (int)((player_angle / (2 * M_PI)) * game->sky_img.width);
	while (x < 1920)
	{
		is_door_hit = 0;
		camerax = 2 * x / (double)1920 - 1;
		raydirx = game->player.dir_x + game->player.plane_x * camerax;
		raydiry = game->player.dir_y + game->player.plane_y * camerax;
		mapx = (int)game->player.x;
		mapy = (int)game->player.y;
		if (raydirx == 0)
			deltadistx = 1e30;
		else
			deltadistx = fabs(1 / raydirx);
		if (raydiry == 0)
			deltadisty = 1e30;
		else
			deltadisty = fabs(1 / raydiry);
		hit = 0;
		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (game->player.x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1 - game->player.x) * deltadistx;
		}
		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (game->player.y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1 - game->player.y) * deltadisty;
		}
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			if (game->map[mapy][mapx] == '1')
				hit = 1;
			else if (game->map[mapy][mapx] == 'D')
			{
				idx = door_idx(game, mapx, mapy);
				if (idx != -1 && game->doors[idx].state != 2)
				{
					if (side == 0)
						perpwalldist = (sidedistx - deltadistx);
					else
						perpwalldist = (sidedisty - deltadisty);
					if (side == 0)
						hitpos = game->player.y + perpwalldist * raydiry;
					else
						hitpos = game->player.x + perpwalldist * raydirx;
					hitpos -= floor(hitpos);
					if (hitpos >= game->doors[idx].open_amount && hitpos < 1.0)
					{
						hit = 1;
						is_door_hit = 1;
					}
				}
			}
		}
		if (is_door_hit == 0)
		{
			if (side == 0)
				perpwalldist = (sidedistx - deltadistx);
			else
				perpwalldist = (sidedisty - deltadisty);
		}
		game->z_buffer[x] = perpwalldist;
		lineheight = (int)(1080 / perpwalldist);
		drawstart = (lineheight * -1) / 2 + 1080 / 2;
		if (drawstart < 0)
			drawstart = 0;
		drawend = lineheight / 2 + 1080 / 2;
		if (drawend >= 1080)
			drawend = 1080 - 1;
		if (side == 0)
			wallx = game->player.y + perpwalldist * raydiry;
		else
			wallx = game->player.x + perpwalldist * raydirx;
		wallx -= floor(wallx);
		if (is_door_hit == 1)
		{
			wallx -= game->doors[idx].open_amount;
			if (wallx < 0.0)
				wallx += 1.0;
		}
		texx = (int)(wallx * 64);
		if (side == 0 && raydirx > 0)
			texx = 64 - texx - 1;
		if (side == 1 && raydiry < 0)
			texx = 64 - texx - 1;
		step = 1.0 * 64 / lineheight;
		texpos = (drawstart - 1080 / 2.0 + lineheight / 2.0) * step;
		y = 0;
		while (y < drawstart)
		{
			sky_texx = (sky_offset_x + x) % game->sky_img.width;
			sky_texy = (y * game->sky_img.height) / (1080 / 2);
			color = get_tex_color(&game->sky_img, sky_texx, sky_texy);
			my_mlx_pixel_put(game, x, y, color);
			y++;
		}
		while (y <= drawend)
		{
			texy = (int)texpos;
			if (texy < 0)
				texy = 0;
			else if (texy >= 64)
				texy = 64 - 1;
			texpos += step;
			if (game->map[mapy][mapx] == 'D')
				color = get_tex_color(&game->tex_d, texx, texy);
			else if (side == 0 && raydirx > 0)
				color = get_tex_color(&game->tex_e, texx, texy);
			else if (side == 0 && raydirx < 0)
				color = get_tex_color(&game->tex_w, texx, texy);
			else if (side == 1 && raydiry > 0)
				color = get_tex_color(&game->tex_s, texx, texy);
			else
				color = get_tex_color(&game->tex_n, texx, texy);
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
	render_sprite(game);
	if (game->player.torch == 0)
		render_torch(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->screen.img, 0,
		0);
	return (1);
}
