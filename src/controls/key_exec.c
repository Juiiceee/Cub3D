/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:44 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 17:37:39 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void head_turn(t_game *game, float angle)
{
	float oldDirX = game->pos.dirx;
	game->pos.dirx = game->pos.dirx * cos(angle) - game->pos.diry * sin(angle);
	game->pos.diry = oldDirX * sin(angle) + game->pos.diry * cos(angle);

	float oldPlaneX = game->pos.planex;
	game->pos.planex = game->pos.planex * cos(angle) - game->pos.planey * sin(angle);
	game->pos.planey = oldPlaneX * sin(angle) + game->pos.planey * cos(angle);
}

void move_left(t_game *game)
{
	double m_x = -game->pos.planex * 0.10;
	double m_y = -game->pos.planey * 0.10;

	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}

void move_right(t_game *game)
{
	double m_x = game->pos.planex * 0.10;
	double m_y = game->pos.planey * 0.10;

	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}

void move_forward(t_game *game)
{
	double m_x = game->pos.dirx * 0.10;
	double m_y = game->pos.diry * 0.10;

	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}

void move_back(t_game *game)
{
	double m_x = -game->pos.dirx * 0.10;
	double m_y = -game->pos.diry * 0.10;

	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}