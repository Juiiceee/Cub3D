/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:08:44 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 13:30:23 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	checkextension(char	*str)
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
		return (1);
	}
	return (error("La map n'a pas la bonne extension"));
}
