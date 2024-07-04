/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCheckInput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:40:14 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/04 14:37:22 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	checkall(t_game *game)
{
	t_bool	good;

	good = False;
	if (checkotherchar(*game))
		good = error("Bad Caracter");
	if (checkwall(*game))
		good = error("Wall error");
	if (checkplayer(game))
		good = error("Player error");
	return (good);
}

int	checkotherchar(t_game game)
{
	int	i;
	int	j;

	i = 0;
	while (game.area[i])
	{
		j = 0;
		while (game.area[i][j])
		{
			if (game.area[i][j] != '0' && game.area[i][j] != '1'
				&& game.area[i][j] != 'N' && game.area[i][j] != 'S'
				&& game.area[i][j] != 'W' && game.area[i][j] != 'E'
				&& game.area[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checkwall(t_game game)
{
	int	i;
	int	j;

	i = 0;
	while (game.area[i])
	{
		j = 0;
		while (game.area[i][j])
		{
			if (game.area[0][j] != '1'
				|| game.area[game.map_info.area_dim.height - 1][j] != '1'
				|| game.area[i][0] != '1'
				|| game.area[i][game.map_info.area_dim.width - 2] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checkplayer(t_game *game)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (game->area[i])
	{
		j = 0;
		while (game->area[i][j])
		{
			if (game->area[i][j] == 'N' || game->area[i][j] == 'S'
				|| game->area[i][j] == 'W' || game->area[i][j] == 'E')
			{
				putpos(game, (int)j, i);
				player++;
			}
			j++;
		}
		i++;
	}
	return (player != 1);
}
