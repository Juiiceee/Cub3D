/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:48:02 by lbehr             #+#    #+#             */
/*   Updated: 2024/07/03 15:03:27 by lbehr            ###   ########.fr       */
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
	while ((int)i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_atoiAlpha(const char *nptr)
{
	long	nbr;
	long	neg;
	int		i;

	nbr = 0;
	neg = 1;
	i = 0;
	while ((nptr[i] <= 13 && nptr[i] >= 9) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	else if (ft_isalpha(nptr[i]))
		return (-1);
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		nbr = nbr * 10 + nptr[i] - 48;
		i++;
	}
	return (nbr * neg);
}

int	ft_strlenback(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
