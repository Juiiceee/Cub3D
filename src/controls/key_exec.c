/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:44 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 18:15:26 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	head_turn(t_game *game, float angle)
{
	float	old_dirx;
	float	old_planex;

	old_dirx = game->pos.dirx;
	old_planex = game->pos.planex;
	game->pos.dirx = game->pos.dirx * cos(angle) - game->pos.diry * sin(angle);
	game->pos.diry = old_dirx * sin(angle) + game->pos.diry * cos(angle);
	game->pos.planex = game->pos.planex * cos(angle)
		- game->pos.planey * sin(angle);
	game->pos.planey = old_planex * sin(angle) + game->pos.planey * cos(angle);
}

void	move_left(t_game *game)
{
	double	m_x;
	double	m_y;

	m_x = -game->pos.planex * 0.10;
	m_y = -game->pos.planey * 0.10;
	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}

void	move_right(t_game *game)
{
	double	m_x;
	double	m_y;

	m_x = game->pos.planex * 0.10;
	m_y = game->pos.planey * 0.10;
	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}

void	move_forward(t_game *game)
{
	double	m_x;
	double	m_y;

	m_x = game->pos.dirx * 0.10;
	m_y = game->pos.diry * 0.10;
	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}

void	move_back(t_game *game)
{
	double	m_x;
	double	m_y;

	m_x = -game->pos.dirx * 0.10;
	m_y = -game->pos.diry * 0.10;
	game->pos.posx = hitbox_x(game->pos.posx, m_x, game->pos.posy, game->area);
	game->pos.posy = hitbox_y(game->pos.posy, m_y, game->pos.posx, game->area);
}
