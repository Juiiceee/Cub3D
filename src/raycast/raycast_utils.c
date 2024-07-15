/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:24:32 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 18:51:02 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calculate_perp_wall_dist(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
		rc->per_wall_dis = (rc->map.x - game->pos.posx + (1 - rc->step.x)
				/ 2) / rc->ray_dir.x;
	else
		rc->per_wall_dis = (rc->map.y - game->pos.posy + (1 - rc->step.y)
				/ 2) / rc->ray_dir.y;
}

void	calculate_line_height(t_game_ray *rc)
{
	rc->line_height = (int)(WIN_HEIGHT / rc->per_wall_dis);
	rc->draw_start = -rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + WIN_HEIGHT / 2;
	if (rc->draw_end >= WIN_HEIGHT)
		rc->draw_end = WIN_HEIGHT - 1;
}

void	hit_point_texture(t_game *game, t_game_ray *rc)
{
	if (rc->side == 0)
		rc->wall_x = game->pos.posy + rc->per_wall_dis * rc->ray_dir.y;
	else
		rc->wall_x = game->pos.posx + rc->per_wall_dis * rc->ray_dir.x;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_width = rc->sprite.width;
	rc->tex_x = (int)(rc->wall_x * (float)rc->tex_width);
	if (rc->side == 0 && rc->ray_dir.x > 0)
		rc->tex_x = rc->tex_width - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->tex_x = rc->tex_width - rc->tex_x - 1;
}

void	init_raycast(t_game *game, t_game_ray *rc, int x)
{
	rc->camera_x = 2 * x / (float)WIN_WIDTH - 1;
	rc->ray_dir.x = game->pos.dirx + game->pos.planex * rc->camera_x;
	rc->ray_dir.y = game->pos.diry + game->pos.planey * rc->camera_x;
	rc->map.x = (int)game->pos.posx;
	rc->map.y = (int)game->pos.posy;
	rc->delta_dis.x = fabs(1 / rc->ray_dir.x);
	rc->delta_dis.y = fabs(1 / rc->ray_dir.y);
}
