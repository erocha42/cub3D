/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 12:43:23 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/16 15:14:07 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_game	game;
	
	if (ac != 2)
	{
		if (ac < 2)
			ft_putstr_fd("Error: Not Enough Arguments\n", 2);
		else
			ft_putstr_fd("Error: Too Many Arguments\n", 2);
		return (0);
	}
	//init_game(&game);
	if (parsing(av, &game))
		return (0);
	if (init_mlx(&game) == 0)
		return (0);
	mlx_loop(game.mlx_ptr);
	return (1);
}
