/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCreate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:32:50 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/01 13:31:16 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	createmap(t_game *game)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(game->map_info.pathmap, O_RDONLY);
	game->map = ft_calloc(game->map_info.heightmap + 1, sizeof(char *));
	if (!game->map)
		return (close(fd), error("Probleme allocation"));
	while (1)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
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
