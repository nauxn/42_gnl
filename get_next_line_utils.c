/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:53:10 by nisim             #+#    #+#             */
/*   Updated: 2026/08/09 15:38:05 by nisim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_findnl(char *s1)
{
	int		i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		if (s1[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	len1;
	char	*str;

	if (!s2)
		return (s1);
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (!str)
		return (free(s1), free(s2), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_fetch_line(char *s1)
{
	int		i;
	char	*line;

	if (!s1 || *s1 == '\0')
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (s1[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[i] = '\0';
	while ((--i) >= 0)
		line[i] = s1[i];
	return (line);
}

char	*ft_strmove(char *s1)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!s1 || !s1[i])
		return (free(s1), NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i])
		return (free(s1), NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) - i));
	if (!str)
		return (free(s1), NULL);
	i++;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}
