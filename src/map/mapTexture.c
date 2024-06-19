/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTexture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:15 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/18 16:06:15 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	recomapinfo(t_game_map_info *info)
{
	int		i;
	char	**map;
	int		fd;

	fd = open(info->pathmap, O_RDONLY);
	i = 0;
	while (get_next_line(fd))
		i++;
	map = malloc(sizeof(char*) * i);
	i = 0;
	if ()
	while (map[i])
	i = 0;
	if (recotexturen(info))
		return (i);
	if (recotexturee(info))
		return (++i);
	if (recotexturee(info))
		return (++i);
	if (recotexturee(info))
		return (++i);
	return (0);
}

int	recotexturen(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "N ", 2))
			i = 2;
		if (!ft_strncmp(line, "NO ", 3))
			i = 3;
		if (i != 0)
		{
			close(fd);
			return (addvaluetexture(i, line, &info->map_texture.north));
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	recotexturee(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "E ", 2))
			i = 2;
		if (!ft_strncmp(line, "EA ", 3))
			i = 3;
		if (i != 0)
			return (close(fd), addvaluetexture(i, line,
					&info->map_texture.east));
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	recotextures(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "S ", 2))
			i = 2;
		if (!ft_strncmp(line, "SU ", 3))
			i = 3;
		if (i != 0)
			return (close(fd), addvaluetexture(i, line,
					&info->map_texture.south));
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	recotexturw(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "W ", 2))
			i = 2;
		if (!ft_strncmp(line, "WE ", 3))
			i = 3;
		if (i != 0)
			return (close(fd), addvaluetexture(i, line,
					&info->map_texture.west));
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}


