/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapAreaCreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:55:59 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/04 14:36:59 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	recoarea(t_game *game)
{
	int	start;
	int	end;
	int	p;

	if (checkifarea(game, &start, &end))
		return (1);
	getareainfo(game, start, end);
	if (createarea(game, start, end))
		return (1);
	p = 0;
	while (game->area[p])
		printf("%s\n", game->area[p++]);
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
			while (game->map[*start] && ft_strlen(game->map[*start
					+ *end]) != 0)
				(*end)++;
			return (0);
		}
		(*start)++;
	}
	return (1);
}

void	getareainfo(t_game *game, int start, int end)
{
	int	i;

	i = 0;
	game->map_info.area_dim.height = end;
	while (i < end)
	{
		if ((int)ft_strlen(game->map[start
				+ i]) > game->map_info.area_dim.width)
			game->map_info.area_dim.width = ft_strlen(game->map[start + i]);
		i++;
	}
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
		game->area[i] = ft_strdup_size(game->map[start + i]);
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
		while (game->area[i][j] == ' ' || game->area[i][j] == '\t'
			|| game->area[i][j] == '\r' || game->area[i][j] == '\v'
			|| game->area[i][j] == '\f')
			j++;
		while (game->area[i][++j])
		{
			if (game->area[i][j] == ' '
				&& j != game->area[i][ft_strlen(game->area[i]) - 1])
				game->area[i][j] = '1';
		}
		i++;
	}
}
