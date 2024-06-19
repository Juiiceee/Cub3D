/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapSize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:56 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/19 16:17:00 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calculateMapSize(char *pathmap, t_game *game)
{
	int		fd;
	char	*str;

	game->map_info.pathmap = ft_strdup(pathmap);
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
	return (close(fd), free(str));
}
