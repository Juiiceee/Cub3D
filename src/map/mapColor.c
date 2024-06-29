/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapColor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:10:56 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/29 17:41:45 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	create_rgb(int *tab)
{
	return (tab[0] << 16 | tab[1] << 8 | tab[2]);
}

int	recoColorC(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->map[i], "C ", 2))
			return (addvalueColor(game->map[i], &game->map_info.color_ceiling));
		i++;
	}
	return (1);
}

int	recoColorF(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->map[i], "F ", 2))
			return (addvalueColor(game->map[i], &game->map_info.color_floor));
		i++;
	}
	return (1);
}

int	addvalueColor(char *line, int *color)
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
		return (1);
	tab = setColorTab(colorsplit);
	if (!tab)
		return (freetab(colorsplit), 1);
	while (j < 3)
	{
		if (!(tab[j] >= 0 && tab[j++] <= 255))
			return (freetab(colorsplit), free(tab), 1);
	}
	*color = create_rgb(tab);
	return (freetab(colorsplit), free(tab), 0);
}

int	*setColorTab(char **color)
{
	int	i;
	int	*tab;

	i = 0;
	while (color[i])
		i++;
	if (i != 3)
		return (0);
	tab = ft_calloc(3,sizeof(int));
	if (!tab)
		return (0);
	tab[0] = ft_atoi(color[0]);
	tab[1] = ft_atoi(color[1]);
	tab[2] = ft_atoi(color[2]);
	return (tab);
}
