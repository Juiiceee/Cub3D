/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTexture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:15 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/17 18:07:16 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	recomapinfo(t_game_map_info *info)
{
	int	i;

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

	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "N ", 2))
			i = 2;
		if (!ft_strncmp(line, "NO ", 3))
			i = 3;
		if (i != 0)
			if (addvaluetexture(i, line, info->map_texture.north))
				return (1);
		free(line);
	}
	return (!ft_isprint(info->map_texture.north[0]));
}

int	recotexturee(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "N ", 2))
			i = 2;
		if (!ft_strncmp(line, "NO ", 3))
			i = 3;
		if (i != 0)
			if (addvaluetexture(i, line, info->map_texture.east))
				return (1);
		free(line);
	}
	return (!ft_isprint(info->map_texture.east[0]));
}

int	recotextures(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "N ", 2))
			i = 2;
		if (!ft_strncmp(line, "NO ", 3))
			i = 3;
		if (i != 0)
			if (addvaluetexture(i, line, info->map_texture.south))
				return (1);
		free(line);
	}
	return (!ft_isprint(info->map_texture.south[0]));
}

int	recotexturw(t_game_map_info *info)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(info->pathmap, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "N ", 2))
			i = 2;
		if (!ft_strncmp(line, "NO ", 3))
			i = 3;
		if (i != 0)
			if (addvaluetexture(i, line, info->map_texture.west))
				return (1);
		free(line);
	}
	return (!ft_isprint(info->map_texture.west[0]));
}
