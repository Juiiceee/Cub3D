/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTexture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:15 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/26 12:20:20 by lbehr            ###   ########.fr       */
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
	if (recotextures(game))
		return (++i);
	if (recotexturew(game))
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
		if (!ft_strncmp(game->area[i], "NO ", 3))
			return (addvaluetexture(game->area[i],
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
		if (!ft_strncmp(game->area[i], "EA ", 3))
			return (addvaluetexture(game->area[i],
					&game->map_info.map_texture.east));
		i++;
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
		if (!ft_strncmp(game->area[i], "SO ", 3))
			return (addvaluetexture(game->area[i],
					&game->map_info.map_texture.south));
		i++;
	}
	return (1);
}

int	recotexturew(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < game->map_info.map_dim.height)
	{
		if (!ft_strncmp(game->area[i], "WE ", 3))
			return (addvaluetexture(game->area[j],
					&game->map_info.map_texture.west));
		i++;
	}
	return (1);
}
