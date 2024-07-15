/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:54 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 13:15:51 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	initall(t_game *game)
{
	int i;

	i = 0;
	inittexture(game);
	initvalue(game);
	while (i < 9)
	{
		game->key[i] = 0;
		i++;	
	}
}

void	inittexture(t_game *game)
{
	game->map_info.map_texture.east = NULL;
	game->map_info.map_texture.south = NULL;
	game->map_info.map_texture.west = NULL;
	game->map_info.map_texture.north = NULL;
}

void	initvalue(t_game *game)
{
	game->map_info.area_dim.width = 0;
}
