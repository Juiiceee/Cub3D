/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:05 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/05 17:23:58 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*removeline(char *buffer)
{
	int		i;
	int		j;
	char	*line_next;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line_next = ft_calloc(ft_strlen(buffer) - i + 1, 1);
	i++;
	j = 0;
	while (buffer[i])
		line_next[j++] = buffer[i++];
	free(buffer);
	return (line_next);
}

char	*reccup(char *buffer)
{
	char	*ligne;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	ligne = ft_calloc(i + 2, 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		ligne[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n' && buffer[i])
	{
		ligne[i] = '\n';
		i++;
	}
	return (ligne);
}

char	*liberation(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*lire(int fd, char *buffer)
{
	char	*buf;
	int		i;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	i = 1;
	while (i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		buffer = liberation(buffer, buf);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = lire(fd, buffer);
	if (!buffer)
		return (NULL);
	line = reccup(buffer);
	buffer = removeline(buffer);
	return (line);
}
