/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:15:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/17 20:25:15 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	path_checker(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, DATA_ERROR);
	close(fd);
	return (1);
}

char	*skip(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (!ft_isprint(line[i]) || line[i] == ' '))
		i++;
	return (&line[i]);
}

int	color_recovery(t_game *game, char *line)
{
	int		i;
	int		color[3];
	char	**tab;

	tab = ft_split(line, ',');
	i = 0;
	while (tab[i])
	{
		color[i] = ft_atoi(tab[i]);
		if (!ft_strisdigits(tab[i]) || color[i] > 255 || color[i] < 0)
		{
			free_tab(tab, 3);
			clean_exit(game, DATA_ERROR);
		}
		i++;
	}
	free_tab(tab, 3);
	return (color[0] << 16 | color[1] << 8 | color[2]);
}

static void	g_c_recovery(t_game *game, char *line, int data_counter[])
{
	char	*arg;

	arg = skip(&line[2]);
	if (!ft_strncmp(&line[0], "F", 1))
	{
		data_counter[4]++;
		game->ground_color = color_recovery(game, arg);
	}
	else if (!ft_strncmp(&line[0], "C", 1))
	{
		data_counter[5]++;
		game->ceiling_color = color_recovery(game, arg);
	}
	else
		clean_exit(game, DATA_ERROR);
}

void	data_recovery(t_game *game, char *line, int data_counter[])
{
	char	*arg;

	arg = skip(&line[2]);
	if (!ft_strncmp(&line[0], "NO", 2) && path_checker(game, arg))
	{
		data_counter[0]++;
		game->n_path = ft_strdup(arg);
	}
	else if (!ft_strncmp(&line[0], "EA", 2) && path_checker(game, arg))
	{
		data_counter[1]++;
		game->e_path = ft_strdup(arg);
	}
	else if (!ft_strncmp(&line[0], "SO", 2) && path_checker(game, arg))
	{
		data_counter[2]++;
		game->s_path = ft_strdup(arg);
	}
	else if (!ft_strncmp(&line[0], "WE", 2) && path_checker(game, arg))
	{
		data_counter[3]++;
		game->w_path = ft_strdup(arg);
	}
	else
		g_c_recovery(game, line, data_counter);
}
