/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:55:49 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/22 15:12:31 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	data_handling(t_game *game)
{
	char	*line;
	char	*temp;
	int		c[6];

	data_counter_init(c);
	line = get_next_line(game->fd);
	while (line && (!c[0] || !c[1] || !c[2] || !c[3] || !c[4] || !c[5]))
	{
		temp = ft_strtrim(line, " \t\n");
		if (temp && temp[0] != '\0')
			game->trim = ft_strtrim(line, "\n");
		if (temp)
			free(temp);
		free(line);
		if (game->trim)
			process_trim(game, c);
		line = get_next_line(game->fd);
	}
	if (line)
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
