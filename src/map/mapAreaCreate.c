/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapAreaCreate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:55:59 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/29 17:32:58 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	recoarea(t_game *game)
{
	int	i;
	int	j;

	if (checkifarea(game, &i, &j))
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
