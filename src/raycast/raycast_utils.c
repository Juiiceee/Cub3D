/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:24:32 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 17:30:55 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void draw_line(t_game *game, int x, int drawStart, int drawEnd, int color)
{
	for (int y = drawStart; y < drawEnd; y++)
	{
		img_pix_put(&game->img, x, y, color);
	}
}

void calculate_perp_wall_dist(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
		rc->perpWallDist =
			(rc->map.x - game->pos.posx + (1 - rc->step.x) / 2) / rc->rayDir.x;
	else
		rc->perpWallDist =
			(rc->map.y - game->pos.posy + (1 - rc->step.y) / 2) / rc->rayDir.y;
}

void calculate_line_height(t_game_ray *rc)
{
	rc->lineHeight = (int)(WIN_HEIGHT / rc->perpWallDist);
	rc->drawStart = -rc->lineHeight / 2 + WIN_HEIGHT / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + WIN_HEIGHT / 2;
	if (rc->drawEnd >= WIN_HEIGHT)
		rc->drawEnd = WIN_HEIGHT - 1;
}

void hit_point_texture(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
		rc->wallX = game->pos.posy + rc->perpWallDist * rc->rayDir.y;
	else
		rc->wallX = game->pos.posx + rc->perpWallDist * rc->rayDir.x;
	rc->wallX -= floor(rc->wallX);
	rc->texWidth = rc->sprite.width;
	rc->texX = (int)(rc->wallX * (float)rc->texWidth);
	if (rc->side == 0 && rc->rayDir.x > 0)
		rc->texX = rc->texWidth - rc->texX - 1;
	if (rc->side == 1 && rc->rayDir.y < 0)
		rc->texX = rc->texWidth - rc->texX - 1;
}

void init_raycast(t_game *game, t_game_ray *rc, int x)
{
	rc->cameraX = 2 * x / (float)WIN_WIDTH - 1;
	rc->rayDir.x = game->pos.dirx + game->pos.planex * rc->cameraX;
	rc->rayDir.y = game->pos.diry + game->pos.planey * rc->cameraX;
	rc->map.x = (int)game->pos.posx;
	rc->map.y = (int)game->pos.posy;
	rc->deltaDist.x = fabs(1 / rc->rayDir.x);
	rc->deltaDist.y = fabs(1 / rc->rayDir.y);
}
