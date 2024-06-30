/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:48:02 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/30 14:39:27 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	error(char *text)
{
	write(2, "Error\n", 7);
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

char	*ft_strdup_size(const char *s, int size)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((sizeof(char)) * (size + 1));
	if (!dup)
		return (NULL);
	while (i < ft_strlen(s) - 1)
	{
		dup[i] = s[i];
		i++;
	}
	if (size > (int)ft_strlen(s))
	{
		while ((int)i < size)
			dup[i++] = ' ';
	}
	dup[i] = '\0';
	return (dup);
}
