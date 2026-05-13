/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:27:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/13 15:18:42 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	error_name_handling(t_error error_name)
{
	if (error_name == NO_ERROR)
		exit(0);
	if (error_name == MALLOC_ERROR)
		ft_putstr_fd("Error: Malloc Error\n", 2);
	if (error_name == MAP_ERROR)
		ft_putstr_fd("Error: Wrong Map\n", 2);
	if (error_name == EXTD_ERROR)
		ft_putstr_fd("Error: Wrong Extension\n", 2);
	if (error_name == FD_ERROR)
		ft_putstr_fd("Error: Wrong FD\n", 2);
	if (error_name == DATA_ERROR)
		ft_putstr_fd("Error: Data Error In .Cub File\n", 2);
	if (error_name == IMG_ERROR)
		ft_putstr_fd("Error: IMG error)\n", 2);
	exit(1);
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
	if (game->trim)
		free(game->trim);
	if (game->mlx_ptr)
	{
		clean_sprites(game);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	error_name_handling(error_name);
}
