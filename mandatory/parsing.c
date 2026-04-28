/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:55:49 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/28 12:56:48 by erocha--         ###   ########.fr       */
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
		data_counter[4]++;data_counter[4]++;
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
	while (line && (!data_counter[0] || !data_counter[1] || !data_counter[2]
		|| !data_counter[3] || !data_counter[4] || !data_counter[5]))
	{
		if (!line[0] || line[0] == '\n')
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

static	char	*search_map(t_game *game, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		while (line[i] && !ft_isprint(line[i]))
			i++;
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S')
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	clean_exit(game, MAP_ERROR);
	return (NULL);
}

static int	nbr_line(t_game *game, char *first_line)
{
	int		nbr_line;
	int		fd;
	char	*line;

	nbr_line = 0;
	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, FD_ERROR);
	line = get_next_line(fd);
	while (line && ft_strncmp(line, first_line, ft_strlen(first_line)))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL)
	{
		close(fd);
		clean_exit(game, MALLOC_ERROR);
	}
	while (line)
	{
		nbr_line++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (nbr_line);
}

static int	search_longest(t_game *game)
{
	int		i;
	int		fd;
	int		longest;
	char	*line;

	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, DATA_ERROR);
	longest = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while(line[i])
			i++;
		if (i > longest)
			longest = i;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (longest);
}

static void	filler(t_game *game, int end_line, char *line, int line_nbr)
{
	int	i;

	i = 0;
	while (i < end_line)
	{
		if (!line[i] && i < end_line)
		{
			line[i + 1] = '\0';
			game->map[line_nbr][i] = ' ';
		}
		else if (line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S')
		{
			if (game->player.x != -1)
				clean_exit(game, MAP_ERROR);
			game->player.y = line_nbr;
			game->player.x = i;
			game->map[line_nbr][i] = line[i];
		}
		else if (!ft_isprint(line[i]))
			game->map[line_nbr][i] = ' ';
		else if (line[i] == '1' || line[i] == '0')
			game->map[line_nbr][i] = line[i];
		else
		{
			game->map[line_nbr][i] = '\0';
			clean_exit(game, MAP_ERROR);
		}
		i++;
	}
	game->map[line_nbr][i] = '\0';
}

static void	mapper(t_game *game, int fd, char *first_line)
{
	char	*line;
	char	*line_trimed;
	int		i;

	game->map_width = search_longest(game);
	i = 0;
	line = first_line;
	game->map = malloc(sizeof(char *) * nbr_line(game, first_line));
	while (line)
	{
		line_trimed = ft_strtrim(line, "\n");
		free(line);
		game->map[i] = malloc(sizeof(char) * game->map_width);
		if (!game->map[i])
			clean_exit(game, MALLOC_ERROR);
		filler(game, game->map_width - 1, line_trimed, i);
		game->map_height++;
		i++;
		free(line_trimed);
		line = get_next_line(fd);
	}
	free(line);
}

void	print_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		printf("%s\n", game->map[i]);
		i++;
	}
}

void	parsing(char *av[], t_game *game)
{
	int	len;
	int	fd;

	game->map_path = av[1];
	len = ft_strlen(game->map_path);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		clean_exit(game, EXTD_ERROR);
	fd = open(game->map_path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		clean_exit(game, FD_ERROR);
	}
	data_handling(game, fd);
	mapper(game, fd, search_map(game, fd));
	valid_map(game);
	print_map(game);
	close(fd);
}
