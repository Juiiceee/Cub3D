/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:15:53 by lbehr             #+#    #+#             */
/*   Updated: 2024/06/11 13:40:24 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <math.h>
# include "../libft/libft.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define WHITE 0xFFFFFF

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	float	posx;
	float	posy;
	float	dirx;
	float	diry;
	float	planex;
	float	planey;
}	t_game;

// maputils.c
/**
 * Checks the extension of a given string.
 *
 * This function takes a string as input and checks if it has a valid extension.
 * It returns an integer value indicating whether the extension is valid or not.
 *
 * @param str The string to check the extension of.
 * @return An integer value indicating the validity of the extension.
 */
int	checkextension(char *str);

//mapchecker.c
/**
 * Displays an error message and return 1.
 *
 * @param text The error message to display.
 * @return Return 1.
 */
int	error(char *text);

#endif