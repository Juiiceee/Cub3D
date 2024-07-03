/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:24:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/03 10:35:02 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	addvaluetexture(char *line, int i, char **map_texture)
{
	int	j;

	j = 0;
	while (line[i] == ' ' && line[i])
		i++;
	while (line[i + j] != ' ' && line[i + j] && line[i + j] != '\n')
		j++;
	*map_texture = ft_substr(line, i, j);
	if (checkextension(*map_texture, ".xpm"))
		return (1);
	if (*map_texture)
		return (0);
	return (error("Probleme allocation"));
}
