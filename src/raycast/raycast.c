/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:24:08 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 17:27:56 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void render_wall(t_game *game, t_game_ray *rc, int x)
{
	int y = rc->drawStart;
	
	while (y <= rc->drawEnd)
    {
        int d = y * 256 - WIN_HEIGHT * 128 + rc->lineHeight * 128;
        int texY = ((d * rc->sprite.height) / rc->lineHeight) / 256;
        char *pixel = rc->sprite.data + (texY *rc->sprite.size_line 
                      + rc->texX * (rc->sprite.bpp / 8));
        img_pix_put(&game->img, x, y, *(int *)pixel);
		y++;
    }
}

void chosen_side(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0) 
	{
		if (rc->rayDir.x > 0)
        rc->sprite = game->textures.west;
		else 
		rc->sprite = game->textures.east;
    } 
	else 
	{
		if (rc->rayDir.y > 0)
        rc->sprite = game->textures.north;
		else 
		rc->sprite = game->textures.south;
    }
}

void dda(t_game *game, t_game_ray *rc)
{
	rc->hit = 0;

	while (rc->hit == 0)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->map.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
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

void calculate_step(t_game *game, t_game_ray *rc)
{
	if (rc->rayDir.x < 0)
	{
		rc->step.x = -1;
		rc->sideDist.x = (game->pos.posx - rc->map.x) * rc->deltaDist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->sideDist.x = (rc->map.x + 1.0 - game->pos.posx) * rc->deltaDist.x;
	}
	if (rc->rayDir.y < 0)
	{
		rc->step.y = -1;
		rc->sideDist.y = (game->pos.posy - rc->map.y) * rc->deltaDist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->sideDist.y = (rc->map.y + 1.0 - game->pos.posy) * rc->deltaDist.y;
	}
}

void raycast(t_game *game)
{
	int x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		t_game_ray raycast;		

		init_raycast(game, &raycast, x);
		calculate_step(game, &raycast);
		dda(game, &raycast);
		calculate_perp_wall_dist(game, &raycast);
		calculate_line_height(&raycast);
		hit_point_texture(game, &raycast);
		render_wall(game, &raycast, x);
		draw_line(game, x, 0, raycast.drawStart, game->map_info.color_ceiling);
		if (raycast.drawEnd != WIN_HEIGHT - 1)
			draw_line(game, x, raycast.drawEnd, WIN_HEIGHT, game->map_info.color_floor);
		x++;
	}
}