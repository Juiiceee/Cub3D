/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCheckInput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:40:14 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 19:24:55 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	checkall(t_game *game)
{
	if (checkotherchar(*game))
		return (error("Bad Caracter"));
	if (checkwall(*game))
		return (error("Wall error"));
	if (checkplayer(game))
		return (error("Player error"));
	return (0);
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

	if (checkwallside(game))
		return (1);
	i = 0;
	while (game.area[i])
	{
		j = 0;
		while (game.area[i][j])
		{
			if (game.area[i][j] == '0')
				if (checkfour(game.area, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checkwallside(t_game game)
{
	int	i;
	int	j;

	i = 0;
	while (game.area[i])
	{
		j = 0;
		while (game.area[i][j])
		{
			if ((i == 0 && game.area[i][j] == '0') || (j == 0
					&& game.area[i][j] == '0')
				|| (j == game.map_info.area_dim.width - 1
					&& game.area[i][j] == '0')
				|| (i == game.map_info.area_dim.height - 1
					&& game.area[i][j] == '0'))
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
