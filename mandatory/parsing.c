/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:55:49 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/15 17:43:18 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checking(char *av[])
{
	int	fd;
	int len;

	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".ber", 4))
	{
		ft_putstr_fd("Error: Wrong Extention\n", 2);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Wrong FD\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}
