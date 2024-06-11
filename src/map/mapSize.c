/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapSize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:23:56 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 15:51:10 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	calculateMapSize(char *map, int *colonne)
{
	int		fd;
	char	*str;
	int		ligne;
	int		test;

	ligne = 0;
	test = 0;
	fd = open(map, O_RDONLY);
	str = get_next_line(fd);
	*colonne = strlenno(str);
	while (1)
	{
		ligne++;
		free(str);
		str = get_next_line(fd);
		if (*colonne != strlenno(str) && str)
			test = 1;
		if (!str)
			break ;
	}
	close(fd);
	if (test == 1)
		return (freeAndReturn(str));
	free(str);
	return (ligne);
}
