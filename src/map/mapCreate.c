/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCreate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:32:50 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 20:34:25 by mda-cunh         ###   ########.fr       */
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

void	putfacing(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->pos.dirx = 0;
		game->pos.diry = -1;
	}
	if (dir == 'S')
	{
		game->pos.dirx = 0;
		game->pos.diry = 1;
	}
	if (dir == 'W')
	{
		game->pos.dirx = -1;
		game->pos.diry = 0;
	}
	if (dir == 'E')
	{
		game->pos.dirx = 1;
		game->pos.diry = 0;
	}
}

void	putpos(t_game *game, int x, int y)
{
	putfacing(game, game->area[y][x]);
	game->area[y][x] = '0';
	game->pos.posx = x + 0.5;
	game->pos.posy = y + 0.5;
}
