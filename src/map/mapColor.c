/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapColor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:10:56 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 19:27:06 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	create_rgb(int *tab)
{
	return (tab[0] << 16 | tab[1] << 8 | tab[2]);
}

int	getcolor_c(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.heightmap)
	{
		if (!ft_strncmp(game->map[i], "C ", 2))
			return (addvaluecolor(game->map[i], &game->map_info.color_ceiling));
		i++;
	}
	return (error("Probleme couleur plafond"));
}

int	getcolor_f(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.heightmap)
	{
		if (!ft_strncmp(game->map[i], "F ", 2))
			return (addvaluecolor(game->map[i], &game->map_info.color_floor));
		i++;
	}
	return (error("Probleme couleur sol"));
}

int	addvaluecolor(char *line, int *color)
{
	int		j;
	int		i;
	char	**colorsplit;
	int		*tab;

	i = 2;
	j = 0;
	while (line[i] == ' ')
		i++;
	colorsplit = ft_split(line + i, ',');
	if (!colorsplit)
		return (error("Probleme allocation"));
	tab = setcolortab(colorsplit);
	if (!tab)
		return (freetab(colorsplit), 1);
	while (j < 3)
	{
		if (!(tab[j] >= 0 && tab[j++] <= 255))
			return (freetab(colorsplit), free(tab),
				error("Intervalle couleur invalide"));
	}
	*color = create_rgb(tab);
	return (freetab(colorsplit), free(tab), 0);
}

int	*setcolortab(char **color)
{
	int	i;
	int	*tab;

	i = 0;
	while (color[i])
		i++;
	if (i != 3)
		return (0);
	tab = ft_calloc(3, sizeof(int));
	if (!tab)
		return (0);
	tab[0] = ft_atoi(color[0]);
	tab[1] = ft_atoi(color[1]);
	tab[2] = ft_atoi(color[2]);
	return (tab);
}
