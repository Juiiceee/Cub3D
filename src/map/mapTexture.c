/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapTexture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:38:15 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/03 10:39:46 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	getmapinfo(t_game *game)
{
	if (gettexturen(game) || gettexturee(game) || gettextures(game)
		|| gettexturew(game) || getcolor_f(game) || getcolor_c(game))
		return (1);
	if (recoarea(game))
		return (1);
	return (0);
}

int	gettexturen(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.heightmap)
	{
		if (!ft_strncmp(game->map[i], "N ", 2))
			return (addvaluetexture(game->map[i], 2,
					&game->map_info.map_texture.north));
		if (!ft_strncmp(game->map[i], "NO ", 3))
			return (addvaluetexture(game->map[i], 3,
					&game->map_info.map_texture.north));
		i++;
	}
	return (error("Probleme texture nord"));
}

int	gettexturee(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.heightmap)
	{
		if (!ft_strncmp(game->map[i], "E ", 2))
			return (addvaluetexture(game->map[i], 2,
					&game->map_info.map_texture.east));
		if (!ft_strncmp(game->map[i], "EA ", 3))
			return (addvaluetexture(game->map[i], 3,
					&game->map_info.map_texture.east));
		i++;
	}
	return (error("Probleme texture est"));
}

int	gettextures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.heightmap)
	{
		if (!ft_strncmp(game->map[i], "S ", 2))
			return (addvaluetexture(game->map[i], 2,
					&game->map_info.map_texture.south));
		if (!ft_strncmp(game->map[i], "SO ", 3))
			return (addvaluetexture(game->map[i], 3,
					&game->map_info.map_texture.south));
		i++;
	}
	return (error("Probleme texture sud"));
}

int	gettexturew(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_info.heightmap)
	{
		if (!ft_strncmp(game->map[i], "W ", 2))
			return (addvaluetexture(game->map[i], 2,
					&game->map_info.map_texture.west));
		if (!ft_strncmp(game->map[i], "WE ", 3))
			return (addvaluetexture(game->map[i], 3,
					&game->map_info.map_texture.west));
		i++;
	}
	return (error("Probleme texture ouest"));
}
