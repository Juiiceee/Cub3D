/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCreate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:32:50 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/19 16:51:29 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	createArea(t_game *game)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(game->map_info.pathmap, O_RDONLY);
	game->area = ft_calloc(game->map_info.map_dim.height, sizeof(char *));
	while (1)
	{
		game->area[i] = get_next_line(fd);
		game->map_info.map_dim.width[i];
		if (!game->area[i])
			break ;
		i++;
	}
	close(fd);
}

void	putpos(t_game *game, int x, int y)
{
	game->pos.posx = x;
	game->pos.posy = y;
}
