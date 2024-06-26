/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCreate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:32:50 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/26 16:46:37 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	createArea(t_game *game)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(game->map_info.pathmap, O_RDONLY);
	game->area = ft_calloc(game->map_info.map_dim.height, sizeof(char *));
	if (!game->area)
		return (close(fd), 1);
	game->map_info.map_dim.width = ft_calloc(game->map_info.map_dim.height,
			sizeof(int));
	if (!game->map_info.map_dim.width)
		return (close(fd), 1);
	while (1)
	{
		game->area[i] = get_next_line(fd);
		game->map_info.map_dim.width[i] = ft_strlen(game->area[i]);
		if (!game->area[i])
			break ;
		i++;
	}
	return (close(fd), 0);
}

void	putpos(t_game *game, int x, int y)
{
	game->pos.posx = x;
	game->pos.posy = y;
}
