/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapChecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:08:44 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 16:52:49 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	checkExtension(char	*str)
{
	int		cb;
	int		i;
	char	*ext;
	int		fd;

	ext = ft_strdup(".cub");
	cb = 0;
	i = 0;
	if (str[i] == '.')
		i++;
	while (str[i] != '.')
		i++;
	while (str[i + cb] == ext[cb] && str[i + cb] && ext[cb])
		cb++;
	free(ext);
	if (cb == 4)
	{
		fd = open(str, O_RDONLY);
		if (fd < 0 || read(fd, 0, 0) < 0)
			return (error("Le fichier ne peut pas etre ouvert"));
		close(fd);
		return (0);
	}
	return (error("La map n'a pas la bonne extension"));
}

int	checkSize(t_game game)
{
	if (game.mesure.line == 0)
		return (error("La saisie n'est pas un rectangle"));
	else if (game.mesure.column > 38 || game.mesure.line > 20)
		return (error("La saisie est trop grande pour l'ecran"));
	return (0);
}
