/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:24:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/19 17:27:24 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	error(char *text)
{
	write(2, "Error\n", 7);
	write(2, text, ft_strlen(text));
	write(2, "\n", 1);
	return (1);
}

int	strlenno(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	freeandreturn(char *str)
{
	free(str);
	return (0);
}

void	freetab(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		free(game->area[i]);
		i++;
	}
	free(game->area);
}

int	addvaluetexture(int i, char *line, char **map_texture)
{
	int j;

	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i + j] != ' ')
		j++;
	*map_texture = ft_substr(line, i, j);
	free(line);
	if (checkExtension(*map_texture, ".xpm"))
		return (1);
	if (*map_texture)
		return (0);
	return (1);
}
