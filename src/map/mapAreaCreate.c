/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapAreaCreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:55:59 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/30 11:55:45 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	recoarea(t_game *game)
{
	int	i;
	int	j;

	if (checkifarea(game, &i, &j))
		return (1);
	if (createarea(game, i, j))
		return (1);
	return (0);
}

int	checkifarea(t_game *game, int *start, int *end)
{
	int	j;

	*end = 0;
	*start = 0;
	while (game->map[*start])
	{
		j = 0;
		while (game->map[*start][j] && ft_isspace(game->map[*start][j]))
			j++;
		if (ft_isdigit(game->map[*start][j]))
		{
			j = 0;
			while (game->map[*start] && ft_strlen(game->map[*start + *end]) != 0)
				(*end)++;
			return (0);
		}
		(*start)++;
	}
	return (1);
}

int	createarea(t_game *game, int start, int end)
{
	int	i;

	i = 0;
	game->area = ft_calloc(end + 1, sizeof(char *));
	if (!game->area)
		return (1);
	while (i < end)
	{
		game->area[i] = ft_strdup(game->map[start + i]);
		if (!game->area[i])
			return (1);
		i++;
	}
	game->area[i] = NULL;
	changevalue(game);
	return (0);
}

void	changevalue(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->area[i])
	{
		j = 0;
		while (game->area[i][j])
		{
			if (ft_isspace(game->area[i][j]))
				game->area[i][j] = '1';
			j++;
		}
		i++;
	}
}