/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handling_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:15:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/20 15:36:20 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	path_checker(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, DATA_ERROR);
	close(fd);
	return (1);
}

int	color_recovery(t_game *game, char *line)
{
	int		i;
	int		c[3];
	char	**tab;

	tab = ft_split(line, ',');
	i = 0;
	while (tab && tab[i])
		i++;
	if (!tab || i != 3)
	{
		free_tab(tab, i);
		clean_exit(game, DATA_ERROR);
	}
	i = -1;
	while (++i < 3)
	{
		c[i] = ft_atoi(tab[i]);
		if (!ft_strisdigits(tab[i]) || c[i] > 255 || c[i] < 0)
		{
			free_tab(tab, 3);
			clean_exit(game, DATA_ERROR);
		}
	}
	free_tab(tab, 3);
	return (c[0] << 16 | c[1] << 8 | c[2]);
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

static void	set_path(char **game_path, int *counter, char *arg)
{
	(*counter)++;
	if (*game_path)
		free(*game_path);
	*game_path = ft_strdup(arg);
}

void	data_recovery(t_game *game, char *line, int data_counter[])
{
	char	*arg;

	arg = skip(&line[2]);
	if (!ft_strncmp(line, "NO", 2) && path_checker(game, arg))
		set_path(&game->n_path, &data_counter[0], arg);
	else if (!ft_strncmp(line, "EA", 2) && path_checker(game, arg))
		set_path(&game->e_path, &data_counter[1], arg);
	else if (!ft_strncmp(line, "SO", 2) && path_checker(game, arg))
		set_path(&game->s_path, &data_counter[2], arg);
	else if (!ft_strncmp(line, "WE", 2) && path_checker(game, arg))
		set_path(&game->w_path, &data_counter[3], arg);
	else
		g_c_recovery(game, line, data_counter);
}
