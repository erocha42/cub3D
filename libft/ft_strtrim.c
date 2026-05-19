/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:53:39 by mchesnea          #+#    #+#             */
/*   Updated: 2026/05/19 18:09:19 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_if_set(char const *s, char const *set, int t)
{
	int	i;
	int	j;
	int	match;

	if (t == 0)
		j = 0;
	else
		j = ft_strlen(s) - 1;
	while (j >= 0 && s[j])
	{
		i = 0;
		match = 0;
		while (set[i])
		{
			if (set[i] == s[j])
			{
				match = 1;
				break ;
			}
			i++;
		}
		if (match == 0)
			break ;
		if (t == 0)
			j++;
		else
			j--;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		last;
	int		i;
	char	*dest;

	if (!set || !s1)
		return (NULL);
	start = check_if_set(s1, set, 0);
	last = check_if_set(s1, set, 1) + 1;
	i = 0;
	if (start >= (int)ft_strlen(s1) || start >= last)
	{
		dest = malloc(1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	dest = malloc(sizeof(char) * (last - start + 1));
	if (!dest)
		return (NULL);
	while (start < last)
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}
