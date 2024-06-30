/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:24:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/30 13:27:10 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	addvaluetexture(char *line, char **map_texture)
{
	int	j;
	int	i;

	i = 3;
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
	return (1);
}
