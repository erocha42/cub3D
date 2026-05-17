/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:22:55 by erocha--          #+#    #+#             */
/*   Updated: 2026/05/17 20:21:46 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	search_longest(t_game *game)
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
		while (line[i])
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

int	nbr_line(t_game *game, char *first_line)
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
	nbr_line = pass_line(fd, line);
	close(fd);
	return (nbr_line);
}

static void	player_update(t_game *game, char *line, int line_nbr, int i)
{
	if (game->player.x != -1)
	{
		free(line);
		clean_exit(game, MAP_ERROR);
	}
	game->player.y = line_nbr + 0.5;
	game->player.x = i + 0.5;
	game->map[line_nbr][i] = line[i];
	game->direction_player = line[i];
}

static void	m_update(t_game *game, char *line, int line_nbr, int i)
{
	if (game->sprite.x != -1)
	{
		free(line);
		clean_exit(game, MAP_ERROR);
	}
	game->sprite.x = i + 0.5;
	game->sprite.y = line_nbr + 0.5;
	game->map[line_nbr][i] = '0';
}

void	filler(t_game *game, size_t end_line, char *line, int line_nbr)
{
	size_t	i;

	i = 0;
	while (i < end_line)
	{
		if (i >= ft_strlen(line))
			game->map[line_nbr][i] = ' ';
		else if (line[i] == 'N' || line[i] == 'W' || line[i] == 'E'
			|| line[i] == 'S')
			player_update(game, line, line_nbr, i);
		else if (line[i] == 'M')
			m_update(game, line, line_nbr, i);
		else if (!ft_isprint(line[i]))
			game->map[line_nbr][i] = ' ';
		else if (line[i] == '1' || line[i] == '0' || line[i] == 'D')
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
