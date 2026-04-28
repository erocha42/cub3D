/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:27:14 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/28 17:11:12 by mchesnea         ###   ########.fr       */
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
	exit(1);
}

void	clean_exit(t_game *game, t_error error_name)
{
	if (game->map)
		free_tab(game->map, game->map_height);
	if (game->fd >= 0)
		close(game->fd);
	error_name_handling(error_name);
}