/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:24:08 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 18:49:55 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render_wall(t_game *game, t_game_ray *rc, int x)
{
	int		y;
	int		d;
	int		tex_y;
	char	*pixel;

	y = rc->draw_start;
	while (y <= rc->draw_end)
	{
		d = y * 256 - WIN_HEIGHT * 128 + rc->line_height * 128;
		tex_y = ((d * rc->sprite.height) / rc->line_height) / 256;
		pixel = rc->sprite.data + (tex_y * rc->sprite.size_line
				+ rc->tex_x * (rc->sprite.bpp / 8));
		img_pix_put(&game->img, x, y, *(int *)pixel);
		y++;
	}
}

void	chosen_side(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir.x > 0)
			rc->sprite = game->textures.west;
		else
			rc->sprite = game->textures.east;
	}
	else
	{
		if (rc->ray_dir.y > 0)
			rc->sprite = game->textures.north;
		else
			rc->sprite = game->textures.south;
	}
}

void	dda(t_game *game, t_game_ray *rc)
{
	rc->hit = 0;
	while (rc->hit == 0)
	{
		if (rc->side_dis.x < rc->side_dis.y)
		{
			rc->side_dis.x += rc->delta_dis.x;
			rc->map.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dis.y += rc->delta_dis.y;
			rc->map.y += rc->step.y;
			rc->side = 1;
		}
		if (game->area[rc->map.y][rc->map.x] != '0')
		{
			rc->hit = 1;
			chosen_side(game, rc);
		}
	}
}

void	calculate_step(t_game *game, t_game_ray *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dis.x = (game->pos.posx - rc->map.x) * rc->delta_dis.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dis.x = (rc->map.x + 1.0 - game->pos.posx) * rc->delta_dis.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dis.y = (game->pos.posy - rc->map.y) * rc->delta_dis.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dis.y = (rc->map.y + 1.0 - game->pos.posy) * rc->delta_dis.y;
	}
}

void	raycast(t_game *game)
{
	int			x;
	t_game_ray	raycast;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_raycast(game, &raycast, x);
		calculate_step(game, &raycast);
		dda(game, &raycast);
		calculate_perp_wall_dist(game, &raycast);
		calculate_line_height(&raycast);
		hit_point_texture(game, &raycast);
		render_wall(game, &raycast, x);
		draw_ceiling(game, x, 0, raycast.draw_start);
		if (raycast.draw_end != WIN_HEIGHT - 1)
			draw_floor(game, x, raycast.draw_end, WIN_HEIGHT);
		x++;
	}
}
