/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapSize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:56 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/30 15:46:29 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	calculatemapsize(char *pathmap, t_game *game)
{
	int		fd;
	char	*str;

	game->map_info.pathmap = ft_strdup(pathmap);
	if (!game->map_info.pathmap)
		return (1);
	game->map_info.heightmap = 0;
	fd = open(game->map_info.pathmap, O_RDONLY);
	str = get_next_line(fd);
	while (1)
	{
		game->map_info.heightmap++;
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
	}
	if (createmap(game))
		return (close(fd), free(game->map_info.pathmap), free(str), 1);
	return (close(fd), free(str), 0);
}
