/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:23:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/08 17:08:25 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_tab_int(int **tab, int limit)
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
