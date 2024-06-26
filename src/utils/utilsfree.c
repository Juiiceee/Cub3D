/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:49:38 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/26 17:05:28 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	freeandreturn(char *str)
{
	free(str);
	return (0);
}

void	freeifnotnull(t_game_map_texture *texture)
{
	if (texture->east)
		free(texture->east);
	if (texture->north)
		free(texture->north);
	if (texture->south)
		free(texture->south);
	if (texture->west)
		free(texture->west);
}

void	freeend(t_game *game)
{
	free(game->map_info.pathmap);
	freeifnotnull(&game->map_info.map_texture);
	freetab(game->area);
	free(game->map_info.map_dim.width);
}

void	freetab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
