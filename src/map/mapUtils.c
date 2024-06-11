/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapUtils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:24:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 15:51:10 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	error(char *text)
{
	write(2,"Error\n", 7);
	write(2, text, ft_strlen(text));
	write(2, "\n", 1);
	return (1);
}

int	strlenno(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	freeAndReturn(char *str)
{
	free(str);
	return (0);
}
