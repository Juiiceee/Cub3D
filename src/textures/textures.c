/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:30:26 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 17:30:32 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void img_pix_put(t_texture *img, int x, int y, int color)
{
	char *pixel;
	int i;

	i = img->bpp - 8;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void load_wall(t_game *game)
{
	t_texture *north = &game->textures.north;
	t_texture *east = &game->textures.east;
	t_texture *west = &game->textures.west;
	t_texture *south = &game->textures.south;

	north->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.north, &north->width, &north->height);
	south->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.south, &south->width, &south->height);
	east->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.east, &east->width, &east->height);
	west->img = mlx_xpm_file_to_image(game->mlx_ptr, 
		game->map_info.map_texture.west, &west->width, &west->height);
	if (!north->img || !south->img || !west->img || !east->img)
		return;
	north->data = mlx_get_data_addr(north->img, &north->bpp, &north->size_line, &north->endian);
	south->data = mlx_get_data_addr(south->img, &south->bpp, &south->size_line, &south->endian);
	east->data = mlx_get_data_addr(east->img, &east->bpp, &east->size_line, &east->endian);
	west->data = mlx_get_data_addr(west->img, &west->bpp, &west->size_line, &west->endian);
}