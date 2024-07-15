/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:30:26 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 18:49:30 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_ceiling(t_game *game, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_end)
	{
		img_pix_put(&game->img, x, y, game->map_info.color_ceiling);
		y++;
	}
}

void	draw_floor(t_game *game, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_end)
	{
		img_pix_put(&game->img, x, y, game->map_info.color_floor);
		y++;
	}
}

void	img_pix_put(t_texture *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

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

void	load_wall(t_game *game)
{
	load_north_wall(game);
	load_south_wall(game);
	load_east_wall(game);
	load_west_wall(game);
}
