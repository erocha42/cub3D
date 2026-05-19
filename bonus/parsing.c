/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:55:49 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/19 18:02:36 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	data_handling(t_game *game)
{
	char	*line;
	char	*temp_check;
	int		data_ctr[6];

	data_counter_init(data_ctr);
	line = get_next_line(game->fd);
	while (line && (!data_ctr[0] || !data_ctr[1] || !data_ctr[2] || !data_ctr[3]
			|| !data_ctr[4] || !data_ctr[5]))
	{
		temp_check = ft_strtrim(line, " \t\n");
		if (!temp_check || temp_check[0] == '\0')
		{
			if (temp_check)
				free(temp_check);
			free(line);
			line = get_next_line(game->fd);
			continue ;
		}
		free(temp_check);
		game->trim = ft_strtrim(line, "\n");
		free(line);
		if (data_ctr[0] > 2 || data_ctr[1] > 2 || data_ctr[2] > 2
			|| data_ctr[3] > 2 || data_ctr[4] > 2 || data_ctr[5] > 2)
			clean_exit(game, DATA_ERROR);
		data_recovery(game, skip(game->trim), data_ctr);
		free(game->trim);
		game->trim = NULL;
		line = get_next_line(game->fd);
	}
	free(line);
}

static char	*search_map(t_game *game)
{
	char	*line;
	int		i;

	line = get_next_line(game->fd);
	i = 0;
	while (line)
	{
		while (line[i] && !ft_isprint(line[i]))
			i++;
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == 'S' || line[i] == 'D')
			return (line);
		free(line);
		line = get_next_line(game->fd);
	}
	free(line);
	clean_exit(game, MAP_ERROR);
	return (NULL);
}

static void	mapper(t_game *game, char *first_line)
{
	char	*line;
	int		i;

	game->map_width = search_longest(game);
	i = 0;
	line = first_line;
	game->map = malloc(sizeof(char *) * nbr_line(game, first_line));
	if (!game->map)
		clean_exit(game, MAP_ERROR);
	while (line)
	{
		game->trim = ft_strtrim(line, "\n");
		free(line);
		game->map[i] = malloc(sizeof(char) * (game->map_width + 1));
		if (!game->map[i])
			clean_exit(game, MALLOC_ERROR);
		game->map_height++;
		filler(game, game->map_width, game->trim, i);
		i++;
		free(game->trim);
		game->trim = NULL;
		line = get_next_line(game->fd);
	}
	free(line);
}

void	parsing(char *av[], t_game *game)
{
	int	len;

	game->map_path = av[1];
	len = ft_strlen(game->map_path);
	if (len < 4 || ft_strncmp(&av[1][len - 4], ".cub", 4))
		clean_exit(game, EXTD_ERROR);
	game->fd = open(game->map_path, O_RDONLY);
	if (game->fd < 0)
		clean_exit(game, FD_ERROR);
	data_handling(game);
	mapper(game, search_map(game));
	if (game->player.x == -1)
		clean_exit(game, MAP_ERROR);
	valid_map(game);
	close(game->fd);
}
