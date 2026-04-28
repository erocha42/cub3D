/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:36:22 by mchesnea          #+#    #+#             */
/*   Updated: 2026/04/27 13:33:51 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *var)
{
	int		i;
	char	*line;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] != '\n' && var[i])
		i++;
	line = ft_substr(var, 0, (i + 1));
	return (line);
}

char	*ft_update_line(char *var)
{
	int		i;
	char	*new_var;

	i = 0;
	while (var[i] && var[i] != '\n')
		i++;
	new_var = ft_substr(var, (i + 1), (ft_strlen(var) - (i + 1)));
	if (!new_var)
	{
		free(var);
		return (NULL);
	}
	free(var);
	return (new_var);
}

void	ft_var(char **var, int fd, char *buff)
{
	char	*tmp;
	int		read_size;

	read_size = 1;
	while (read_size > 0 && ft_strchr(var[fd], '\n') == NULL)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0)
		{
			if (var[fd] != NULL)
			{
				free(var[fd]);
				var[fd] = NULL;
			}
			return ;
		}
		buff[read_size] = '\0';
		tmp = var[fd];
		var[fd] = ft_strjoin(tmp, buff);
		free(tmp);
	}
}

char	*get_next_line(int fd)
{
	static char	*var[] = {NULL};
	char		*buff;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ft_var(var, fd, buff);
	free(buff);
	if (!var[fd])
		return (NULL);
	if (var[fd] && var[fd][0] == '\0')
	{
		free(var[fd]);
		var[fd] = NULL;
		return (NULL);
	}
	line = ft_extract_line(var[fd]);
	if (!line)
		return (NULL);
	var[fd] = ft_update_line(var[fd]);
	return (line);
}
