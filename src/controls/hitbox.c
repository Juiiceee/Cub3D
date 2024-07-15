/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:33:47 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/07/15 18:15:38 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	hitbox_x(double pos_x, double move_x, double pos_y, char **map)
{
	int		y_out;
	int		y_in;
	int		future_x;

	y_in = (int)(pos_y + 0.1);
	y_out = (int)(pos_y - 0.1);
	if (move_x < 0)
		future_x = (int)(pos_x + move_x - 0.1);
	else
		future_x = (int)(pos_x + move_x + 0.1);
	if (map[y_in][future_x] != '1'
		&& map[y_out][future_x] != '1')
		pos_x += move_x;
	return (pos_x);
}

double	hitbox_y(double pos_y, double move_y, double pos_x,	char **map)
{
	int		x_out;
	int		x_in;
	int		future_y;

	x_in = (int)(pos_x + 0.1);
	x_out = (int)(pos_x - 0.1);
	if (move_y < 0)
		future_y = (int)(pos_y + move_y - 0.1);
	else
		future_y = (int)(pos_y + move_y + 0.1);
	if (map[future_y][x_in] != '1'
		&& map[future_y][x_out] != '1')
		pos_y += move_y;
	return (pos_y);
}
