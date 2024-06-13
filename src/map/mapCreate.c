/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapCreate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:32:50 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/13 07:07:06 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	inputArea(char *map, t_game *game)
{
	int		fd;
	int		i;
	char	*text;

	i = 0;
	fd = open(map, O_RDONLY);
	game->area = createArea(game->mesure.line,
			game->mesure.column);
	while (i < game->mesure.line)
	{
		text = get_next_line(fd);
		game->area[i] = ft_strncpy(game->area[i],
				text, game->mesure.column);
		free(text);
		i++;
	}
	close(fd);
}

char	**createArea(int ligne, size_t colonne)
{
	char	**area;
	int		i;

	i = 0;
	area = ft_calloc(ligne, sizeof(char *));
	while (i < ligne)
	{
		area[i] = ft_calloc(colonne + 1, 1);
		i++;
	}
	return (area);
}

void	putpos(t_game *game, int x, int y)
{
	game->pos.posX = x;
	game->pos.posY = y;
}
