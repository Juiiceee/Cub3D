/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:48:02 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/15 19:25:38 by mda-cunh         ###   ########.fr       */
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

char	*ft_strdup_size(char *s, int size)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc((sizeof(char)) * (size + 1));
	if (!dup)
		return (NULL);
	while (i < strlenno(s))
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	isnotcorrect(char c)
{
	return (c != '0' && c != '1' && c != 'N' && c != 'E' && c != 'S'
		&& c != 'W');
}

int	checkfour(char **map, int cols, int rows)
{
	if ((isnotcorrect(map[cols - 1][rows])) || (isnotcorrect(map[cols][rows
				- 1])) || (isnotcorrect(map[cols + 1][rows]))
		|| (isnotcorrect(map[cols][rows + 1])))
		return (1);
	return (0);
}
