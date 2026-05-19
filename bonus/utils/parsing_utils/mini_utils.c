/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:45:53 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/19 15:36:24 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (!ft_isprint(line[i]) || line[i] == ' '))
		i++;
	return (&line[i]);
}

int	ft_strisdigits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	data_counter_init(int data_counter[])
{
	data_counter[0] = 0;
	data_counter[1] = 0;
	data_counter[2] = 0;
	data_counter[3] = 0;
	data_counter[4] = 0;
	data_counter[5] = 0;
}

int	pass_line(int fd, char *line)
{
	int	nbr_line;

	nbr_line = 0;
	while (line)
	{
		nbr_line++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (nbr_line);
}

void	free_tab(char **tab, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
