/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:54:13 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/13 18:59:42 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_sprites(t_game *game)
{
	if (game->tex_n.img)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_n.img);
		game->tex_n.img = NULL;
	}
	if (game->tex_e.img)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_e.img);
		game->tex_e.img = NULL;
	}
	if (game->tex_s.img)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_s.img);
		game->tex_s.img = NULL;
	}
	if (game->tex_w.img)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_w.img);
		game->tex_w.img = NULL;
	}
}

int	init_images(t_game *game)
{
	game->tex_n.img = mlx_xpm_file_to_image(game->mlx_ptr, game->n_path,
			&game->tex_n.width, &game->tex_n.height);
	if (!game->tex_n.img)
		clean_exit(game, NO_ERROR);
	game->tex_n.addr = mlx_get_data_addr(game->tex_n.img, &game->tex_n.bpp,
			&game->tex_n.line_len, &game->tex_n.endian);
	game->tex_e.img = mlx_xpm_file_to_image(game->mlx_ptr, game->e_path,
			&game->tex_e.width, &game->tex_e.height);
	if (!game->tex_e.img)
		clean_exit(game, NO_ERROR);
	game->tex_e.addr = mlx_get_data_addr(game->tex_e.img, &game->tex_e.bpp,
			&game->tex_e.line_len, &game->tex_e.endian);
	game->tex_s.img = mlx_xpm_file_to_image(game->mlx_ptr, game->s_path,
			&game->tex_s.width, &game->tex_s.height);
	if (!game->tex_s.img)
		clean_exit(game, NO_ERROR);
	game->tex_s.addr = mlx_get_data_addr(game->tex_s.img, &game->tex_s.bpp,
			&game->tex_s.line_len, &game->tex_s.endian);
	game->tex_w.img = mlx_xpm_file_to_image(game->mlx_ptr, game->w_path,
			&game->tex_w.width, &game->tex_w.height);
	if (!game->tex_w.img)
		clean_exit(game, NO_ERROR);
	game->tex_w.addr = mlx_get_data_addr(game->tex_w.img, &game->tex_w.bpp,
			&game->tex_w.line_len, &game->tex_w.endian);
	game->tex_sprite.img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->sprite_path, &game->tex_sprite.width,
			&game->tex_sprite.height);
	if (!game->tex_sprite.img)
	{
		clean_sprites(game);
		return (0);
	}
	game->tex_sprite.addr = mlx_get_data_addr(game->tex_sprite.img,
			&game->tex_sprite.bpp, &game->tex_sprite.line_len,
			&game->tex_sprite.endian);
	game->tex_d.img = mlx_xpm_file_to_image(game->mlx_ptr,
			"./sprites/Door-6.xpm", &game->tex_d.width, &game->tex_d.height);
	if (!game->tex_d.img)
		clean_exit(game, NO_ERROR);
	game->tex_d.addr = mlx_get_data_addr(game->tex_d.img, &game->tex_d.bpp,
			&game->tex_d.line_len, &game->tex_d.endian);
	printf("tex_d: width=%d height=%d\n", game->tex_d.width,
		game->tex_d.height);
	game->tex_w.addr = mlx_get_data_addr(game->tex_w.img, &game->tex_w.bpp,
			&game->tex_w.line_len, &game->tex_w.endian);
	return (1);
}
