/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:27:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/19 12:06:45 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error_name_handling(t_error error_name)
{
	if (error_name == NO_ERROR)
		exit(0);
	if (error_name == MALLOC_ERROR)
		ft_putstr_fd("Error:\n Malloc Error\n", 2);
	if (error_name == MAP_ERROR)
		ft_putstr_fd("Error:\n Wrong Map\n", 2);
	if (error_name == EXTD_ERROR)
		ft_putstr_fd("Error:\n Wrong Extension\n", 2);
	if (error_name == FD_ERROR)
		ft_putstr_fd("Error:\n Wrong FD\n", 2);
	if (error_name == DATA_ERROR)
		ft_putstr_fd("Error:\n Data Error In .Cub File\n", 2);
	if (error_name == IMG_ERROR)
		ft_putstr_fd("Error:\n IMG error)\n", 2);
	exit(1);
}

static void	clean_mlx_ptrs(t_game *game)
{
	clean_sprites(game);
	if (game->screen.img)
		mlx_destroy_image(game->mlx_ptr, game->screen.img);
	if (game->tex_sprite.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_sprite.img);
	if (game->sky_img.img)
		mlx_destroy_image(game->mlx_ptr, game->sky_img.img);
	if (game->tex_d.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_d.img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
}

static void	clean_exit2(t_game *game)
{
	if (game->trim)
		free(game->trim);
	if (game->doors)
		free(game->doors);
	if (game->heatmap)
	{
		free_tab_int(game->heatmap, game->map_height);
		game->heatmap = NULL;
	}
	if (game->has_audio == 1)
	{
		ma_sound_uninit(&game->monster_sound);
		ma_sound_uninit(&game->step_sound);
		ma_sound_uninit(&game->jumpscare_sound);
		ma_engine_uninit(&game->audio_engine);
	}
	if (game->mlx_ptr)
		clean_mlx_ptrs(game);
}

void	clean_exit(t_game *game, t_error error_name)
{
	char	*gnl_rest;

	if (game->map)
		free_tab(game->map, game->map_height);
	if (game->n_path)
		free(game->n_path);
	if (game->s_path)
		free(game->s_path);
	if (game->e_path)
		free(game->e_path);
	if (game->w_path)
		free(game->w_path);
	if (game->fd > 0)
	{
		gnl_rest = get_next_line(game->fd);
		while (gnl_rest)
		{
			free(gnl_rest);
			gnl_rest = get_next_line(game->fd);
		}
		close(game->fd);
	}
	clean_exit2(game);
	error_name_handling(error_name);
}
