/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:31:12 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 18:35:18 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	load_north_wall(t_game *game)
{
	t_texture	*north;

	north = &game->textures.north;
	north->img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map_info.map_texture.north, &north->width, &north->height);
	if (!north->img)
		return ;
	north->data = mlx_get_data_addr(north->img, &north->bpp,
			&north->size_line, &north->endian);
}

void	load_south_wall(t_game *game)
{
	t_texture	*south;

	south = &game->textures.south;
	south->img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map_info.map_texture.south, &south->width, &south->height);
	if (!south->img)
		return ;
	south->data = mlx_get_data_addr(south->img, &south->bpp,
			&south->size_line, &south->endian);
}

void	load_east_wall(t_game *game)
{
	t_texture	*east;

	east = &game->textures.east;
	east->img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map_info.map_texture.east, &east->width, &east->height);
	if (!east->img)
		return ;
	east->data = mlx_get_data_addr(east->img, &east->bpp,
			&east->size_line, &east->endian);
}

void	load_west_wall(t_game *game)
{
	t_texture	*west;

	west = &game->textures.west;
	west->img = mlx_xpm_file_to_image(game->mlx_ptr,
			game->map_info.map_texture.west, &west->width, &west->height);
	if (!west->img)
		return ;
	west->data = mlx_get_data_addr(west->img, &west->bpp,
			&west->size_line, &west->endian);
}
