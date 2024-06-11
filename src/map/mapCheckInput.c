/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCheckInput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:40:14 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 16:52:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	checkAll(t_game *game)
{
	t_bool	good;

	good = False;
	if (checkOtherChar(game))
		good = error("Bad Caracter");
	if (checkWall(game))
		good = error("Wall error");
	if (checkPlayer(game))
		good = error("Player error");
	return (good);
}

int	checkOtherChar(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mesure.line)
	{
		j = 0;
		while (j < game->mesure.column)
		{
			if (game->area[i][j] != '0' && game->area[i][j] != '1'
					&& game->area[i][j] != 'N' && game->area[i][j] != 'S'
					&& game->area[i][j] != 'E' && game->area[i][j] != 'W')
				return (True);
			j++;
		}
		i++;
	}
	return (False);
}

int	checkWall(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mesure.line)
	{
		j = 0;
		while (j < game->mesure.column)
		{
			if (game->area[0][j] != '1'
					|| game->area[game->mesure.line - 1][j] != '1'
					|| game->area[i][0] != '1'
					|| game->area[i][game->mesure.column - 1] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	checkPlayer(t_game *game)
{
	int		i;
	int		j;
	int		player;

	i = 0;
	player = 0;
	while (i < game->mesure.line)
	{
		j = 0;
		while (j < game->mesure.column)
		{
			if (game->area[i][j] == 'N' || game->area[i][j] == 'S'
				|| game->area[i][j] == 'E' || game->area[i][j] == 'W')
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
