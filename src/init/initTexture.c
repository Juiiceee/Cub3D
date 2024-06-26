/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initTexture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:54 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/26 12:13:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	inittexture(t_game *game)
{
	game->map_info.map_texture.east = NULL;
	game->map_info.map_texture.south = NULL;
	game->map_info.map_texture.west = NULL;
	game->map_info.map_texture.north = NULL;
}
