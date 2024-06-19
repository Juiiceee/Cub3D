/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTexture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:15 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/19 17:59:24 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	recomapinfo(t_game *game)
{
	int	i;

	i = 0;
	if (recotexturen(game))
		return (i);
	if (recotexturee(game))
		return (++i);
	if (recotexturee(game))
		return (++i);
	if (recotexturee(game))
		return (++i);
	return (0);
}

int	recotexturen(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->area[i], "N ", 2))
			j = 2;
		if (!ft_strncmp(game->area[i], "NO ", 3))
			j = 3;
		if (j != 0)
			return (addvaluetexture(j, game->area[i],
					&game->map_info.map_texture.north));
		i++;
	}
	return (1);
}

int	recotexturee(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->area[i], "E ", 2))
			j = 2;
		if (!ft_strncmp(game->area[i], "EA ", 3))
			j = 3;
		if (j != 0)
			return (addvaluetexture(j, game->area[i],
					&game->map_info.map_texture.east));
	}
	return (1);
}

int	recotextures(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->area[i], "S ", 2))
			j = 2;
		if (!ft_strncmp(game->area[i], "SU ", 3))
			j = 3;
		if (j != 0)
			return (addvaluetexture(j, game->area[i],
					&game->map_info.map_texture.south));
	}
	return (1);
}

int	recotexturw(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->area[i], "W ", 2))
			j = 2;
		if (!ft_strncmp(game->area[i], "WE ", 3))
			j = 3;
		if (j != 0)
			return (addvaluetexture(i, game->area[j],
					&game->map_info.map_texture.west));
	}
	return (1);
}
