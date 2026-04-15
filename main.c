/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:43:23 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/15 17:27:49 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_game	game;
	
	if (ac != 2)
	{
		ft_putstr_fd("Error: Not Enough Arguments\n", 2);
		return (0);
	}
	//init_game(&game);
	if (checking(av) == 0)
	{
		return (0);
	}
	if (init_mlx(&game) == 0)
	{
		return (0);
	}
	mlx_loop(game.mlx_ptr);
	return (1);
}
