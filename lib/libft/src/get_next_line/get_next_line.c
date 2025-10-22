/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:49:08 by aranger           #+#    #+#             */
/*   Updated: 2023/12/04 12:09:51 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*set_line(char *line)
{
	char	*cutline;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	if (line[i] == '\0')
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] == '\0')
			return (line);
		i++;
	}
	cutline = ft_calloc(i + 2, sizeof(char));
	if (cutline == NULL)
		return (NULL);
	i = 0;
	while (line [i] != '\n' && line[i] != '\0')
	{
		cutline[i] = line[i];
		i++;
	}
	cutline[i] = line[i];
	return (cutline);
}

static char	*set_rest(char *line)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\n')
	{
		if (line[i] == '\0')
			return (NULL);
		i++;
	}
	i++;
	rest = ft_calloc(ft_strlen(line) - i + 1, sizeof(char));
	if (rest == NULL)
		return (NULL);
	while (line [i] != '\0')
	{
		rest[j] = line[i];
		i++;
		j++;
	}
	return (rest);
}

static char	*read_buffer(int fd, char *rest)
{
	char	*line;
	char	*tmp;
	int		readsize;

	readsize = 1;
	if (rest)
		line = rest;
	else
		line = ft_calloc((1), sizeof(char));
	while (line)
	{
		tmp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (tmp == NULL)
			return (NULL);
		readsize = read(fd, tmp, BUFFER_SIZE);
		if (readsize <= 0)
		{
			free(tmp);
			break ;
		}
		line = ft_strjoin(line, tmp);
		if (ft_strrchr(line, '\n') != NULL)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*tmp;
	char		*line;

	if (fd < 0)
		return (NULL);
	tmp = read_buffer(fd, rest);
	line = set_line(tmp);
	rest = set_rest(tmp);
	if (tmp)
		free(tmp);
	if (!line && !rest)
		return (NULL);
	return (line);
}
