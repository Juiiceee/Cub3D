/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapSize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:56 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/26 17:05:03 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	calculateMapSize(char *pathmap, t_game *game)
{
	int		fd;
	char	*str;

	game->map_info.pathmap = ft_strdup(pathmap);
	if (!game->map_info.pathmap)
		return (1);
	game->map_info.map_dim.height = 0;
	fd = open(game->map_info.pathmap, O_RDONLY);
	str = get_next_line(fd);
	while (1)
	{
		game->map_info.map_dim.height++;
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
	}
	if (createArea(game))
		return (close(fd), free(game->map_info.pathmap), free(str), 1);
	return (close(fd), free(str), 0);
}
