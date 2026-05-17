/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:27:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/15 14:32:57 by mchesnea         ###   ########.fr       */
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

static void	clean_exit_2(t_game *game)
{
	if (game->trim)
		free(game->trim);
	if (game->mlx_ptr)
	{
		clean_sprites(game);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
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
	clean_exit_2(game);
	error_name_handling(error_name);
}
