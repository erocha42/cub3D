/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:55:49 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/17 16:32:08 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	data_counter_init(int data_counter[])
{
	data_counter[0] = 0;
	data_counter[1] = 0;
	data_counter[2] = 0;
	data_counter[3] = 0;
	data_counter[4] = 0;
	data_counter[5] = 0;
}

static int	path_checker(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, DATA_ERROR);
	close(fd);
	return (1);
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

static int	color_recovery(t_game *game, char *line)
{
	int		i;
	int		j;
	int		color[3];
	char	**tab;
	
	tab = ft_split(line, ',');
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			j++;
		color[i] = ft_atoi(tab[i]);
		if (!ft_strisdigits(tab[i]) || color[i] > 255 || color[i] < 0)
		{
			free_tab(tab);
			clean_exit(game, DATA_ERROR);
		}
		i++;
	}
	free_tab(tab);
	return (color[0] << 16 | color[1] << 8 | color[2]);
}

char	*skip(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (!ft_isprint(line[i]) || line[i] == ' '))
		i++;
	return (&line[i]);
}

static void	g_c_recovery(t_game *game, char *line, int data_counter[])
{
	char *arg;

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

static void	data_recovery(t_game *game, char *line, int data_counter[])
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

static void data_handling(t_game *game, int fd)
{
	char	*line;
	char	*line_trimed;
	int		data_counter[6];

	data_counter_init(data_counter);
	line = get_next_line(fd);
	while (line)
	{
		if (!line[0] || line[0] != '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		line_trimed = ft_strtrim(line, "\n");
		free(line);
		if (data_counter[0] > 2 || data_counter[1] > 2 || data_counter[2] > 2
			|| data_counter[3] > 2 || data_counter[4] > 2 || data_counter[5] > 2)
			clean_exit(game, DATA_ERROR);
		data_recovery(game, skip(line_trimed), data_counter);
		free(line_trimed);
		line = get_next_line(fd);
	}
	free(line);
}

//static void	mapper(t_game *game, int fd)
//{
//	char	*line;
//	int		nbr_line;
//	int		longest_line;
//	int		i;

//	nbr_line = line_counter(fd);
//	longest_line = search_longest(fd);
//	game->map = malloc(sizeof(char *) * nbr_line);
//	if (!game->map)
//		clean_exit(game, MALLOC_ERROR);
//	i = 0;
//	while (i < nbr_line)
//	{
//		game->map[i] = malloc(sizeof(char) * longest_line);
//		if (!game->map[i])
//			clean_exit(game, MALLOC_ERROR);
//		i++;
//	}
	
//}

//static int	search_longest(int fd)
//{
//	int		i;
//	int		longest;
//	char	*line;

//	longest = 0;
//	line = get_next_line(fd);
//	while (line)
//	{
//		i = 0;
//		while(line[i])
//			i++;
//		if (i > longest)
//			longest = i;
//		free(line);
//		line = get_next_line(fd);
//	}
//	free(line);
//	return (longest);
//}

void	parsing(char *av[], t_game *game)
{
	int	len;
	int	fd;

	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		clean_exit(game, EXTD_ERROR);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		clean_exit(game, FD_ERROR);
	}
	data_handling(game, fd);
	//mapper(game, fd);
	close(fd);
	return (0);
}
