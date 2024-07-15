/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:54 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 17:38:11 by mda-cunh         ###   ########.fr       */
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

void set_fov(t_game *game, double fov_degrees)
{
	double fov_radians = (fov_degrees)*M_PI / 180.0;
	double half_fov_tan = tan(fov_radians / 2.0);

	game->pos.planex = game->pos.diry * half_fov_tan;
	game->pos.planey = -game->pos.dirx * half_fov_tan;
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
